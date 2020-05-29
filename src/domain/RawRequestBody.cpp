#include "domain/RawRequestBody.hpp"

using namespace getit::domain;

RawRequestBody::RawRequestBody(const std::string& contentType):
    contentType(contentType)
{
    
}

RawRequestBody::RawRequestBody():
    RawRequestBody(DEF_CONTENT_TYPE)
{
    
}

void RawRequestBody::setBody(const std::string& body)
{
    this->body = body;
}

std::string RawRequestBody::getContentType()
{
    return this->contentType;
}

std::string RawRequestBody::getBody()
{
    return this->body;
}

size_t RawRequestBody::getSize()
{
    return this->body.size();
}