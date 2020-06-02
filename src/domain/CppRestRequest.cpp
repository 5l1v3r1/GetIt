#include "domain/CppRestRequest.hpp"

#include <utility>

using namespace getit::domain;

CppRestRequest::CppRestRequest(const std::string& method, const std::string& uri, const client::http_client& client):
    Request(method, uri),
    client(client)
{
    
}

CppRestRequest::CppRestRequest(const std::string& method, const std::string& uri):
    CppRestRequest(method, uri, client::http_client(uri))
{
    
}

void CppRestRequest::send(std::function<void(Response*)> callback)
{
    http_request request = this->buildRequest();

    this->client.request(request).then([=](http_response restResponse) {
        const auto& response = getit::domain::CppRestRequest::buildResponse(std::move(restResponse));

        callback(response);
    });
}


http_request CppRestRequest::buildRequest()
{
    http_request request;
    request.set_method(this->method);

    this->addCookiesToRequest(&request);
    this->addHeadersToRequest(&request);
    this->addBodyToRequest(&request);

    return request;
}

void CppRestRequest::addCookiesToRequest(http_request* request)
{
    const auto& cookieHeaderName = "Cookie";
    std::string cookieHeaderValue;

    for (const auto& [cookie, value]: this->cookies) {
        auto cookieHeaderFormat = boost::format("%1%%2%=%3%; ") % cookieHeaderValue % cookie % value;
        cookieHeaderValue = cookieHeaderFormat.str();
    }

    request->headers().add(cookieHeaderName, cookieHeaderValue);
}

void CppRestRequest::addHeadersToRequest(http_request* request)
{
    for (auto const& [header, value]: this->headers) {
        request->headers().add(header, value);
    }
}

void CppRestRequest::addBodyToRequest(http_request* request)
{
    if (this->body != nullptr) {
        request->set_body(this->body->getBody(), this->body->getContentType());
    }
}

Response* CppRestRequest::buildResponse(http_response restResponse)
{
    const auto& response = new Response();
    bool ignoreContentType = true;

    response->body = restResponse.extract_string(ignoreContentType).get();
    response->statusCode = restResponse.status_code();

    for (auto const& [header, value]: restResponse.headers()) {
        response->headers.insert({header, value});
    }

    return response;
}
