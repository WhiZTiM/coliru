#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>

/* Thsis macro is used to simplify the definitions of several parser combinator functions */
#define ALLOCATE(...) { parser *_result = malloc(sizeof *_result); if (!_result) return NULL; *_result = ((parser) { __VA_ARGS__ }); return _result; }

typedef struct parser {
    enum {
        CHAR,
        STRING,
        SATISFY,
        MANY,
        AND,
        OR,
        TRY
    } type;
    union {
        char c;
        char *s;
        int (*predicate)(int);
        struct {
            struct parser const * restrict first;
            struct parser const * restrict second;
        };
    };
} parser;

struct parse_result {
    bool success;
    size_t consumed;
    size_t written;
};

struct parse_result parse(struct parser const *p, char const *s, void *result)
{
#define RESULT(s, c, w) ((struct parse_result) { s, c, w })
    switch (p->type) {
    case CHAR: {
        bool success = p->c == s[0];
        if (success && result) ((char *) result)[0] = s[0];
        return RESULT(success, 1, 1);
    }
    case STRING: {
        bool success = strncmp(p->s, s, strlen(p->s)) == 0;
        if (success && result) strcpy(result, p->s);
        return RESULT(success, strlen(p->s), strlen(p->s));
    }
    case SATISFY: {
        bool success = p->predicate(s[0]);
        if (success && result) ((char *) result)[0] = s[0];
        return RESULT(success, 1, 1);
    }
    case MANY: {
        struct parse_result r;
        size_t consumed, written;
        consumed = written = 0;
        while (r = parse(p->first, s, result), r.success) {
            s += r.consumed; consumed += r.consumed;
            result = (char *) result + r.written; written += r.written;
        }
        return RESULT(true, consumed, written);
    }
    case AND: {
        struct parse_result r1 = parse(p->first, s, result);
        if (!r1.success) return RESULT(false, 0, 0);
        s += r1.consumed;
        result = (char *) result + r1.written;
        struct parse_result r2 = parse(p->second, s, result);
        r2.written += r1.written;
        r2.consumed += r1.consumed;
        return r2;
    }
    case OR: {
        struct parse_result r1 = parse(p->first, s, result);
        if (r1.success) return r1;
        else return parse(p->second, s, result);
    }
    }
#undef RESULT
}

parser *satisfy(int (*predicate)(int))
{
    ALLOCATE(.type = SATISFY, .predicate = predicate);
}

parser *many(parser const *p)
{
    ALLOCATE(.type = MANY, .first = p);
}

parser *many1(parser const *p)
{
    parser *many_parser = many(p);
    if (!many_parser) return NULL;
    ALLOCATE(.type = AND, .first = p, .second = many_parser);
}

int main(void)
{
    char s[] = "14853";
    char out[sizeof s];

    parser *integer = many1(satisfy(isdigit));

    (void) parse(integer, s, out);

    out[sizeof s - 1] = 0;

    puts(out);
}