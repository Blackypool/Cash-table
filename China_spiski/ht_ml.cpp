#include "ht_ml.hpp"


void go_to_html(int skolko_kartinok)
{
    FILE *fp_out = fopen("dumpy/dot.png/go_to_html.html", "w");
    AsserT(fp_out == NULL, file_errorr, );

    fprintf(fp_out, "<!DOCTYPE html>\n<html>\n<head>\n    <meta charset = \"UTF-8\">\n</head>\n<body>\n    <div class = \"image-container\">\n");

    for(int i = 0; i < skolko_kartinok; ++i)
    {
        fprintf(fp_out, "        <img src = \"phg_spisok%d.png\" alt = \"testik\" vspace = \"40\">\n\n" , i);

        fprintf(fp_out, "        <h1>__________________________________________________________________________________________________________________________________</h1>\n");
    }

    fprintf(fp_out, "    </div>\n</body>\n</html>");

    fclose(fp_out);
}
