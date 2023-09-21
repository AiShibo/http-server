//
// Created by asnic on 8/30/2023.
//

#include "constants.h"


const char *upper_html =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <title>File List</title>\n"
        "    <style>\n"
        "        body, h1, ul, li {\n"
        "            margin: 0;\n"
        "            padding: 0;\n"
        "        }\n"
        "        body {\n"
        "            background-color: #1a1a1a;\n"
        "            font-family: Arial, Helvetica, sans-serif;\n"
        "            color: #eee;\n"
        "        }\n"
        "        .container {\n"
        "            max-width: 800px;\n"
        "            margin: auto;\n"
        "            background-color: #222;\n"
        "            padding: 2em;\n"
        "            border-radius: 8px;\n"
        "            box-shadow: 0 0 10px rgba(0, 0, 0, 0.3);\n"
        "        }\n"
        "        h1 {\n"
        "            font-size: 1.8em;\n"
        "            color: #eee;\n"
        "            margin-bottom: 1em;\n"
        "        }\n"
        "        ul {\n"
        "            list-style: none;\n"
        "        }\n"
        "        li {\n"
        "            background-color: #333;\n"
        "            margin: 8px 0;\n"
        "            padding: 12px;\n"
        "            border-radius: 4px;\n"
        "            transition: background-color 0.2s ease;\n"
        "        }\n"
        "        a {\n"
        "            text-decoration: none;\n"
        "            color: #eee;\n"
        "        }\n"
        "        li:hover {\n"
        "            background-color: #444;\n"
        "        }\n"
        "    </style>\n"
        "</head>\n"
        "<body>\n"
        "    <div class=\"container\">\n";

const char *lower_html =
        "        </ul>\n"
        "    </div>\n"
        "</body>\n"
        "</html>";

const struct file_type type_list[] = {
        { "html", "text/html" },
        { "htm",  "text/html" },
        { "jpg",  "image/jpeg" },
        { "jpeg", "image/jpeg" },
        { "png",  "image/png" },
        { "css",  "text/css" },
        { "txt",  "text/plain" },
        { "gif",  "image/gif" },
        { "ico",  "image/x-icon" },
        { "mp3",  "audio/mpeg" },
        { "mp4",  "video/mp4" },
        { "json", "application/json" },
        { "js",   "application/javascript" },
        { "xml",  "application/xml" },
        { "pdf",  "application/pdf" },
        {0, 0},
};
