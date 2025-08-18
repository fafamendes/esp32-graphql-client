#include "GraphQLClient.h"

// Using a larger document size for the response to accommodate potentially large data payloads and error messages.
// The request document can be smaller as it only contains the query and variables.
StaticJsonDocument<1024> responseDoc;
StaticJsonDocument<512> requestDoc;

/**
 * @brief Constructs a new GraphQLClient instance.
 * @param endpoint The full URL of the GraphQL server endpoint.
 */
GraphQLClient::GraphQLClient(const char* endpoint) : _endpoint(endpoint) {}

/**
 * @brief Sets a custom HTTP header for all subsequent requests.
 * @param key The header name.
 * @param value The header value.
 */
void GraphQLClient::setHeader(const char* key, const char* value) {
    Header* newHeader = new Header{key, value, _headers};
    _headers = newHeader;
}

/**
 * @brief Executes a GraphQL query.
 * @param query The GraphQL query string.
 * @param variables A JsonObject containing the variables for the query.
 * @return A GraphQLResponse object with the server's response.
 */
GraphQLResponse GraphQLClient::query(const char* query, JsonObject variables) {
    return execute(query, variables);
}

/**
 * @brief Executes a GraphQL mutation.
 * @param mutation The GraphQL mutation string.
 * @param variables A JsonObject containing the variables for the mutation.
 * @return A GraphQLResponse object with the server's response.
 */
GraphQLResponse GraphQLClient::mutate(const char* mutation, JsonObject variables) {
    return execute(mutation, variables);
}

/**
 * @brief Internal helper to execute a GraphQL operation (query or mutation).
 * @param operation The GraphQL operation string.
 * @param variables A JsonObject containing the variables.
 * @return A GraphQLResponse object.
 */
GraphQLResponse GraphQLClient::execute(const char* operation, JsonObject variables) {
    _httpClient.begin(_endpoint);
    _httpClient.addHeader("Content-Type", "application/json");

    // Add custom headers
    Header* current = _headers;
    while (current) {
        _httpClient.addHeader(current->key, current->value);
        current = current->next;
    }

    // Create request body
    requestDoc.clear();
    requestDoc["query"] = operation;
    if (!variables.isNull()) {
        requestDoc["variables"] = variables;
    }

    String requestBody;
    serializeJson(requestDoc, requestBody);

    // Make the request
    int httpCode = _httpClient.POST(requestBody);

    if (httpCode > 0) {
        String payload = _httpClient.getString();
        deserializeJson(responseDoc, payload);

        _httpClient.end();

        return {
            responseDoc["data"].as<JsonObject>(),
            responseDoc["errors"].as<JsonArray>(),
            responseDoc.containsKey("errors")
        };
    } else {
        _httpClient.end();
        // Create a synthetic error response for network errors
        responseDoc.clear();
        JsonArray errors = responseDoc.createNestedArray("errors");
        JsonObject error = errors.createNestedObject();
        error["message"] = "HTTP Error: " + String(httpCode) + " " + _httpClient.errorToString(httpCode);
        
        return {
            responseDoc["data"].as<JsonObject>(),
            errors,
            true
        };
    }
}