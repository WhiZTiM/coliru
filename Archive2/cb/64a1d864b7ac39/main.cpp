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
    XmlAttribute *next;
};

struct xmlElement
{
    char *name;
    char *value;
    XmlElement *prev;
    XmlElement *next;
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
    
    start = *pos;
    
    if (!*start) return 0;
    while (!isspace(**pos) && **pos && **pos != endmark) ++(*pos);
    
    word = calloc(1, *pos - start + 1);
    memcpy(word, start, *pos - start);
    return word;
}

void freeAttributeListStep(XmlAttribute *first, XmlAttribute *attribute)
{
    if (attribute->next != first) freeAttributeListStep(first, attribute->next);
    free(attribute->value);
    free(attribute->name);
}

void freeAttributeList(XmlAttribute *first)
{
    if (first) freeAttributeListStep(first, first);
}

void freeElementList(XmlElement *first);
void freeElementListStep(XmlElement *first, XmlElement *element)
{
    freeElementList(element->children);
    freeAttributeList(element->attributes);
    if (element->next != first) freeElementListStep(first, element->next);
    free(element->value);
    free(element->name);
    free(element);
}

void freeElementList(XmlElement *first)
{
    if (first) freeElementListStep(first, first);
}

void freeDoc(XmlDoc *doc)
{
    if (doc)
    {
        freeElementList(doc->root);
        free(doc);
    }
}

XmlAttribute *parseAttribute(const char **xmlText)
{
    const char *startval;
    XmlAttribute *attribute = calloc(1, sizeof(XmlAttribute));
    attribute->next = attribute->prev = attribute;
    
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
    freeAttributeList(attribute);
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
    element->prev = element->next = element;
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
        if (element->attributes)
        {
            attribute->prev = element->attributes->prev;
            attribute->next = element->attributes;
            element->attributes->prev->next = attribute;
            element->attributes->prev = attribute;
        }
        else
        {
            element->attributes = attribute;
        }
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
                if (*xmlText != startval)
                {
                    element->value = calloc(1, *xmlText - startval + 1);
                    memcpy(element->value, startval, *xmlText - startval);
                }
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
                if (element->children)
                {
                    childnode->prev = element->children->prev;
                    childnode->next = element->children;
                    element->children->prev->next = childnode;
                    element->children->prev = childnode;
                }
                else
                {
                    element->children = childnode;
                }
                childnode = 0;
            }
        }
        else ++(*xmlText);
    }
    
parseElement_fail:
    freeElementList(element);
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
                    freeElementList(doc->root);
                    free(doc);
                }
                ++p;
            }
            else
            {
                if (doc->root)
                {
                    freeElementList(doc->root);
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
            freeElementList(doc->root);
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
    
    if (att) do
    {
        if (!strcmp(attname, att->name) && !strcmp(attval, att->value))
        {
            return element->value;
        }
        att = att->next;
    } while (att != element->attributes);
    
    if (elem) do
    {
        value = valueByAttribute(elem, attname, attval);
        if (value) return value;
        elem = elem->next;
    } while (elem != element->children);
    
    return 0;
}

void dumpXmlAttribute_int(XmlAttribute *s, XmlAttribute *a, int shift)
{
    int i;

    if (!a) return;

    for (i=0; i<shift; ++i) fputs(" ", stdout);
    printf("[XmlAttribute]: %s, value: %s\n", a->name, a->value);
    if (a->next != s) dumpXmlAttribute_int(s, a->next, shift);
}

void dumpXmlAttribute(XmlAttribute *a, int shift)
{
    dumpXmlAttribute_int(a,a,shift);
}

void dumpXmlElement(XmlElement *e, int shift);
void dumpXmlElement_int(XmlElement *s, XmlElement *e, int shift)
{
    int i;
    
    if (!e) return;

    for (i=0; i<shift; ++i) fputs(" ", stdout);
    printf("[XmlElement]: %s\n", e->name);
    dumpXmlAttribute(e->attributes, shift+2);
    if (e->children)
    {
        dumpXmlElement(e->children, shift+2);
    }
    else if (e->value)
    {
        for (i=0; i<shift; ++i) fputs(" ", stdout);
        printf("  value: %s\n", e->value);
    }
    if (e->next != s) dumpXmlElement_int(s, e->next, shift);
}

void dumpXmlElement(XmlElement *e, int shift)
{
    dumpXmlElement_int(e,e,shift);
}

void dumpXmlData(XmlDoc *doc)
{
    if (!doc)
    {
        puts("No document found.");
        return;
    }

    puts("[XmlDoc]:");
    dumpXmlElement(doc->root,2);
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
    
    dumpXmlData(doc);
    if (!doc)
    {
        puts("Parse error.");
        return 1;
    }

    val = valueByAttribute(doc->root, argv[1], argv[2]);
    if (!val) val = "<not found>";
    
    printf("*[%s='%s'] : %s\n", argv[1], argv[2], val);
    free(doc);
    
    return 0;
}
