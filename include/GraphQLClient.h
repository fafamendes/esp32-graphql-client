#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

/**
 * @struct GraphQLResponse
 * @brief Represents the response from a GraphQL server.
 * 
 * This struct holds the data and/or errors returned by a GraphQL query or mutation.
 */
struct GraphQLResponse {
    /**
     * @brief The 'data' field from the GraphQL response.
     * 
     * It's a read-only JSON object. You can access values like `response.data["key"]`.
     */
    const JsonObject data;

    /**
     * @brief The 'errors' field from the GraphQL response.
     * 
     * It's a read-only JSON array containing any errors that occurred.
     */
    const JsonArray errors;

    /**
     * @brief True if the response contains any errors in the 'errors' field.
     */
    bool hasError = false;

    /**
     * @brief Gets a formatted error message from the 'errors' array.
     * @return A String containing the concatenated error messages, or an empty string if there are no errors.
     */
    String getErrorMessage() const {
        if (!hasError || errors.isNull() || errors.size() == 0) {
            return "";
        }
        String errorMessage = "";
        for (JsonObject error : errors) {
            errorMessage += error["message"].as<String>() + "\n";
        }
        return errorMessage;
    }
};

/**
 * @class GraphQLClient
 * @brief A simple GraphQL client for ESP32, inspired by Apollo Client. 
 * 
 * This class handles sending queries and mutations to a GraphQL server over HTTP.
 */
class GraphQLClient {
public:
    /**
     * @brief Constructs a new GraphQLClient instance.
     * @param endpoint The full URL of the GraphQL server endpoint.
     */
    GraphQLClient(const char* endpoint);

    /**
     * @brief Sets a custom HTTP header for all subsequent requests.
     * 
     * Useful for authentication tokens, e.g., `setHeader("Authorization", "Bearer YOUR_TOKEN")`.
     * @param key The header name.
     * @param value The header value.
     */
    void setHeader(const char* key, const char* value);

    /**
     * @brief Executes a GraphQL query.
     * @param query The GraphQL query string.
     * @param variables A JsonObject containing the variables for the query.
     * @return A GraphQLResponse object with the server's response.
     */
    GraphQLResponse query(const char* query, JsonObject variables);

    /**
     * @brief Executes a GraphQL mutation.
     * @param mutation The GraphQL mutation string.
     * @param variables A JsonObject containing the variables for the mutation.
     * @return A GraphQLResponse object with the server's response.
     */
    GraphQLResponse mutate(const char* mutation, JsonObject variables);

private:
    const char* _endpoint;
    HTTPClient _httpClient;
    struct Header {
        String key;
        String value;
        Header* next;
    };
    Header* _headers = nullptr;

    /**
     * @brief Internal helper to execute a GraphQL operation (query or mutation).
     * @param operation The GraphQL operation string.
     * @param variables A JsonObject containing the variables.
     * @return A GraphQLResponse object.
     */
    GraphQLResponse execute(const char* operation, JsonObject variables);
};