#ifndef REQUESTS_H
#define REQUESTS_H

#include <cpr/cpr.h>
#include "tarUtils.h"


inline cpr::Response get(const std::string& url) {
    return cpr::Get(cpr::Url{url});
}

inline cpr::Response post(const std::string& url, const cpr::Body& body) {
    return cpr::Post(cpr::Url{url}, cpr::Body{body});
}

inline cpr::Response put(const std::string& url, const cpr::Body& body) {
    return cpr::Put(cpr::Url{url}, cpr::Body{body});
}

inline cpr::Response del(const std::string& url) {
    return cpr::Delete(cpr::Url{url});
}

inline cpr::Response patch(const std::string& url, const cpr::Body& body) {
    return cpr::Patch(cpr::Url{url}, cpr::Body{body});
}

inline void download(const std::string& url, const std::string& path) {
    cpr::Response r = get(url);
    std::ofstream out(path);
    out << r.text;
    out.close();
}

inline void downloadTar(const std::string& url, const std::string& path) {
    cpr::Response r = get(url);
    extractTar(r.text, path);
}

#endif