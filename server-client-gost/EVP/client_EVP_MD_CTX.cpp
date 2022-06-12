#include "../client-gost.h"

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <openssl/evp.h>
#include <iomanip>

using namespace std;

ClassClientGostLog CLIENT_GOST_MD_LOG;

/*
    The advantage of this higher-level interface is that you just need
    to replace the EVP_sha256() call with another digest function, such
    as EVP_sha512(), to use a different digest. So it adds flexibility.
*/

bool ClassClientGost::create_password_hash(const std::string& unhashed_password,
                   std::string& hashed_password)
{
    CLIENT_GOST_MD_LOG.string_void = "ClassClientGost::create_password_hash()";
    bool success = false;

    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if(context == NULL) {
        CLIENT_GOST_MD_LOG.string_message = "context is null";
        CLIENT_GOST_MD_LOG.logger();
        return false;
    }

    if(!EVP_DigestInit_ex(context, EVP_sha256(), NULL)) {
        CLIENT_GOST_MD_LOG.string_message = "EVP_DigestInit_ex(): error";
        CLIENT_GOST_MD_LOG.logger();
        return false;
    }
    if(!EVP_DigestUpdate(context, unhashed_password.c_str(),
                        unhashed_password.length())) {
        CLIENT_GOST_MD_LOG.string_message = "EVP_DigestUpdate(): error";
        CLIENT_GOST_MD_LOG.logger();
        return false;
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    if(!EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
        CLIENT_GOST_MD_LOG.string_message = "EVP_DigestFinal_ex(): error";
        CLIENT_GOST_MD_LOG.logger();
        return false;
    }

    std::stringstream ss;
    for(unsigned int i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    hashed_password = ss.str();
    success = true;

    EVP_MD_CTX_free(context);

    return success;
}
