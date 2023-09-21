//
// Created by asnic on 8/30/2023.
//

#ifndef RE_FILE_SERVER_CONSTANTS_H
#define RE_FILE_SERVER_CONSTANTS_H

#define HTTP_HEADER_SIZE 8192 // the maximum allowed http header size

/*
 * define the pair struct that describes the
 * relationship between the file extension name
 * and its http type. this is required for the
 * browser to correctly display the file
 */
struct file_type {
    const char* extension;
    const char* http_type;
};

/*
 * How the HTML was outputted:
 *
 *
 * the file server requires to dynamically generate hyperlinks
 * to the files according to the content of the library. The html was
 * split into 2 parts by the HTML tags (table rows) that needs to be
 * generated in a loop
 */

// the upper part of the html
extern const char *upper_html;
// the lower part of the html
extern const char *lower_html;
// the array of file_type elements containing common file extensions and their http type
extern const struct file_type type_list[];

#endif //RE_FILE_SERVER_CONSTANTS_H
