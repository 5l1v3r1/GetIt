#include "domain/CppRestRequest.hpp"

#include <utility>

using namespace getit::domain;

CppRestRequest::CppRestRequest(const std::string& method, const std::string& uri, const web::http::client::http_client& client):
    Request(method, uri),
    client(client)
{
    
}

CppRestRequest::CppRestRequest(const std::string& method, const std::string& uri):
    CppRestRequest(method, uri, web::http::client::http_client(uri))
{
    
}

void CppRestRequest::send(std::function<void(Response*)> callback)
{
    web::http::http_request request = this->buildRequest();  

    this->client.request(request).then([=](web::http::http_response restResponse) {
        const auto& response = getit::domain::CppRestRequest::buildResponse(std::move(restResponse));

        callback(response);
    });
}


web::http::http_request CppRestRequest::buildRequest()
{
    web::http::http_request request;
    request.set_method(this->method);

    this->addHeadersToRequest(&request);
    this->addBodyToRequest(&request);

    return request;
}

void CppRestRequest::addHeadersToRequest(web::http::http_request* request)
{
    for (auto const& [header, value]: this->headers) {
        request->headers().add(header, value);
    }
}

void CppRestRequest::addBodyToRequest(web::http::http_request* request)
{
    if (this->body != nullptr) {
        request->set_body(this->body->getBody(), this->body->getContentType());
    }
}

Response* CppRestRequest::buildResponse(web::http::http_response restResponse)
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
