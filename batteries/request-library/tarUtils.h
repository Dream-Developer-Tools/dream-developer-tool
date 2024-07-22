#ifndef TARUTILS_H
#define TARUTILS_H

#include <iostream>
#include <string>
#include <archive.h>

void extractTarFromBuffer(const std::string& buffer, const std::string& path) {
    // using libarchive to extract the tar file
    struct archive* a;
    struct archive_entry* entry;
    int r;
    a = archive_read_new();
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    r = archive_read_open_memory(a, buffer.c_str(), buffer.size());
    if (r != ARCHIVE_OK) {
        std::cerr << "Failed to open the archive" << std::endl;
        return;
    }
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        r = archive_read_extract(a, entry, 0);
        if (r != ARCHIVE_OK) {
            std::cerr << "Failed to extract the archive" << std::endl;
            return;
        }
    }
    archive_read_close(a);
    archive_read_free(a);
}


#endif