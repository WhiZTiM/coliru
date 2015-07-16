#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct xmlDoc;
typedef struct xmlDoc XmlDoc;

struct xmlAttribute;
typedef struct xmlAttribute XmlAttribute;

struct xmlElement;
typedef struct xmlElement XmlElement;

struct xmlAttribute
{
    char *name;
    char *value;
    XmlAttribute *prev;
};

struct xmlElement
{
    char *name;
    char *value;
    XmlElement *prev;
    XmlAttribute *attributes;
    XmlElement *children;
};

struct xmlDoc
{
    XmlElement *root;
};

void skipWs(const char **pos)
{
    while (isspace(**pos)) ++(*pos);
}

char *readBareWord(const char **pos, char endmark)
{
    const char *start;
    char *word;
    
    skipWs(pos);
    start = *pos;
    
    if (!*start) return 0;
    while (!isspace(**pos) && **pos && **pos != endmark) ++(*pos);
    
    word = calloc(1, *pos - start + 1);
    memcpy(word, start, *pos - start);
    return word;
}

void freeAttribute(XmlAttribute *attribute)
{
    if (attribute)
    {
        freeAttribute(attribute->prev);
        free(attribute->value);
        free(attribute->name);
    }
}

void freeElement(XmlElement *element)
{
    if (element)
    {
        freeElement(element->children);
        freeAttribute(element->attributes);
        freeElement(element->prev);
        free(element->value);
        free(element->name);
        free(element);
    }
}

void freeDoc(XmlDoc *doc)
{
    if (doc)
    {
        freeElement(doc->root);
        free(doc);
    }
}

XmlAttribute *parseAttribute(const char **xmlText)
{
    const char *startval;
    XmlAttribute *attribute = calloc(1, sizeof(XmlAttribute));
    
    attribute->name = readBareWord(xmlText, '=');
    if (!attribute->name || !**xmlText) goto parseAttribute_fail;
    skipWs(xmlText);
    if (**xmlText != '=') goto parseAttribute_fail;
    ++(*xmlText);
    skipWs(xmlText);
    if (**xmlText != '"') goto parseAttribute_fail;
    ++(*xmlText);
    
    startval = *xmlText;
    while (**xmlText && **xmlText != '"') ++(*xmlText);
    if (!**xmlText) goto parseAttribute_fail;
    attribute->value = calloc(1, *xmlText - startval + 1);
    memcpy(attribute->value, startval, *xmlText - startval);
    ++(*xmlText);
    return attribute;
    
parseAttribute_fail:
    freeAttribute(attribute);
    return 0;
}

XmlElement *parseElement(const char **xmlText)
{
    XmlElement *element;
    XmlElement *childnode;
    XmlAttribute *attribute;
    const char *startval;
    
    ++(*xmlText);
    if (!**xmlText || **xmlText == '/') return 0;
    
    element = calloc(1, sizeof(XmlElement));
    element->name = readBareWord(xmlText, '>');
    if (!element->name || !**xmlText) goto parseElement_fail;
    
    childnode = 0;
    attribute = 0;
    while (1)
    {
        skipWs(xmlText);
        if (!**xmlText) goto parseElement_fail;
    
        if (**xmlText == '>')
        {
            ++(*xmlText);
            break;
        }
        if (**xmlText == '/')
        {
            ++(*xmlText);
            skipWs(xmlText);
            if (!**xmlText) goto parseElement_fail;
            if (**xmlText != '>') goto parseElement_fail;
            ++(*xmlText);
            return element;
        }
        attribute = parseAttribute(xmlText);
        if (!attribute) goto parseElement_fail;
        attribute->prev = element->attributes;
        element->attributes = attribute;
        attribute = 0;
        if (!**xmlText) goto parseElement_fail;
    }
    
    startval = *xmlText;
    while (**xmlText)
    {
        if (**xmlText == '<')
        {
            if ((*xmlText)[1] == '/')
            {
                element->value = calloc(1, *xmlText - startval + 1);
                memcpy(element->value, startval, *xmlText - startval);
                *xmlText += 2;
                skipWs(xmlText);
                if (!**xmlText) goto parseElement_fail;
                if (strncmp(*xmlText, element->name, strlen(element->name))) goto parseElement_fail;
                *xmlText += strlen(element->name);
                skipWs(xmlText);
                if (!**xmlText || **xmlText != '>') goto parseElement_fail;
                ++(*xmlText);
                return element;
            }
            else
            {
                childnode = parseElement(xmlText);
                if (!childnode) goto parseElement_fail;
                childnode->prev = element->children;
                element->children = childnode;
                childnode = 0;
            }
        }
        else ++(*xmlText);
    }
    
parseElement_fail:
    freeElement(element);
    return 0;
}

XmlDoc *parseXml(const char *xmlText)
{
    XmlDoc* doc = malloc(sizeof(XmlDoc));
    const char *p = xmlText;
    
    doc->root = 0;
    while(*p)
    {
        if (*p == '<')
        {
            if (p[1] == '!' || p[1] == '?')
            {
                ++p;
                while (*p && *p != '>') ++p;
                if (!*p)
                {
                    freeElement(doc->root);
                    free(doc);
                }
                ++p;
            }
            else
            {
                if (doc->root)
                {
                    freeElement(doc->root);
                    free(doc);
                    return 0;
                }
                else
                {
                    doc->root = parseElement(&p);
                    if (!doc->root)
                    {
                        free(doc);
                        return 0;
                    }
                }
            }
        }
        else if (isspace(*p))
        {
            skipWs(&p);
        }
        else
        {
            freeElement(doc->root);
            free(doc);
            return 0;
        }
    }
    
    return doc;
}

const char *valueByAttribute(XmlElement *element, const char *attname, const char *attval)
{
    const char *value;
    XmlAttribute *att = element->attributes;
    XmlElement *elem = element->children;
    
    while (att)
    {
        if (!strcmp(attname, att->name) && !strcmp(attval, att->value))
        {
            return element->value;
        }
        att = att->prev;
    }
    
    while (elem)
    {
        value = valueByAttribute(elem, attname, attval);
        if (value) return value;
        elem = elem->prev;
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    XmlDoc *doc;
    size_t bufsize = 1024;
    size_t readsize;
    size_t readtotal;
    const char *val;
    char *buffer;

    FILE *file = 0;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s attrname attrval [filename]", argv[0]);
        return 1;
    }

    if (argc > 3)
    {
        file = fopen(argv[3], "r");
    }
    if (!file) file = stdin;

    buffer = malloc(bufsize);
    if (!buffer) return 1;
    
    readtotal = 0;
    while ((readsize = fread(buffer, 1, bufsize, file)) == bufsize)
    {
        readtotal += readsize;
        bufsize *= 2;
        if (!realloc(buffer, bufsize)) return 1;
    }
    readtotal += readsize;
    buffer[readtotal] = 0;
    
    doc = parseXml(buffer);
    free(buffer);
    
    if (!doc)
    {
        puts("Parse error.");
        return 1;
    }

    val = valueByAttribute(doc->root, argv[1], argv[2]);
    if (!val) val = "<not found>";
    
    printf("*[%s='%s'] : %s\n", argv[1], argv[2], val);
    
    return 0;
}

