/**
 * @file basic_query.ino
 * @brief A basic example demonstrating how to send a GraphQL query with variables.
 * 
 * This example connects to a Wi-Fi network, sends a GraphQL query to a specified server,
 * and prints the response to the Serial monitor.
 * 
 * @note For this example to work, you need to create a `config.h` file in this directory
 *       with your Wi-Fi credentials and GraphQL server endpoint.
 *       See the `config.h.example` file for the required definitions.
 */

#include <WiFi.h>
#include <GraphQLClient.h>
#include <ArduinoJson.h>
#include "config.h" // Contains WIFI_SSID, WIFI_PASSWORD, and GRAPHQL_ENDPOINT

// Instantiate the GraphQL client
GraphQLClient client(GRAPHQL_ENDPOINT);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // You can set custom headers here, for example, for authentication
  // client.setHeader("Authorization", "Bearer YOUR_API_TOKEN");
}

void loop() {
  // 1. Define the GraphQL query
  // This query asks for the name of a repository, specified by the $owner and $name variables.
  const char* getRepoInfo = R"(
    query GetRepoInfo($owner: String!, $name: String!) {
      repository(owner: $owner, name: $name) {
        name
        description
        url
      }
    }
  )";

  // 2. Define the variables for the query
  // The StaticJsonDocument size should be adjusted based on the complexity of your variables.
  StaticJsonDocument<200> variables;
  variables["owner"] = "fafamendes";
  variables["name"] = "esp32-graphql-client";

  // 3. Execute the query
  Serial.println("Executing query...");
  GraphQLResponse response = client.query(getRepoInfo, variables.as<JsonObject>());

  // 4. Process the response
  if (response.hasError) {
    Serial.println("GraphQL Error:");
    Serial.println(response.getErrorMessage());
  } else {
    Serial.println("GraphQL Response:");
    // You can access the data like this:
    const char* repoName = response.data["repository"]["name"];
    const char* repoDescription = response.data["repository"]["description"];
    
    Serial.print("Repository Name: ");
    Serial.println(repoName);
    Serial.print("Description: ");
    Serial.println(repoDescription);

    // Or print the whole data object
    Serial.println("\nFull data object:");
    serializeJsonPretty(response.data, Serial);
    Serial.println();
  }

  // Wait for 60 seconds before the next request
  Serial.println("\nWaiting 60 seconds to run again...");
  delay(60000);
}