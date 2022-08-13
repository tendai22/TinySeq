//
//
//

#include <stdio.h>
#include <string.h>

size_t strlcpy (char *dest, const char *src, size_t len)
{
    return snprintf (dest, len, "%s", src);
}

int main(int ac, char **av)
{
    FILE *fp, *op;
    char *src;

    while ((src = *av++) != NULL) {
        char *ext = strrchr(src, '.');
        if (ext == NULL) {
            continue;
        }
        ext++;
        if (strcmp(ext, "zf") != 0) {
            continue;
        }
        if ((fp = fopen (src, "r")) == NULL) {
            continue;
        }
        char dest[512];
        strlcpy(dest, src, 512);
        if ((ext = strrchr(dest, '.')) == NULL) {
            continue;
        }
        strcpy(ext + 1, "c");
        fprintf(stderr, "src: %s, dest: %s\n", src, dest);
        //
        // stringize
        //
        if ((op = fopen (dest, "w")) == NULL) {
            continue;
        }
        *ext = '\0';
        char buf[512];
        fprintf (op, "const char zf_src_%s_file[] = {\n", dest);
        int first = 1, c, col;
        col = 0;
        while ((c = fgetc(fp)) != EOF) {
            if (first) {
                fprintf(op, "  ");
                first = 0;
            }
            fprintf (op, "0x%02x, ", c);
            if (col++ == 15) {
                fprintf (op, "\n");
                first = 1;
                col = 0;
            }
        }
        fprintf (op, "  0\n};\n");
        fclose (op);
        fclose (fp);
    }
}