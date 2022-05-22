#ifndef __HELPERFUNCTIONS_H
#define __HELPERFUNCTIONS_H

#include <jsoncpp/json/json.h>

inline Json::Value makeJSON(std::string x) {
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();

    Json::Value root;
    std::string errors;

    bool parsingSuccessful = reader->parse(
        x.c_str(),
        x.c_str() + x.size(),
        &root,
        &errors
    );
    delete reader;
    //parsingSuccessful ??!??! std::cout << "Parsing error!\n";
    if (!parsingSuccessful) {
    	return Json::Value(); //TODO error cos it didnt parse
    }
    return root;
}

#endif
