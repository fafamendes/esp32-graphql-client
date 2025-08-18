# Basic Query Example

This example demonstrates how to use the `GraphQLClient` library to send a simple query with variables to a GraphQL server.

## Purpose

The code connects to a Wi-Fi network and sends a query to the public GitHub GraphQL API. It requests information about a specific repository (`esp32-graphql-client` by `fafamendes`) and prints the response to the Serial monitor.

## How to Use

1.  **Copy the Config File:**
    -   Rename the `config.h.example` file in this directory to `config.h`.

2.  **Edit `config.h`:**
    -   Open the new `config.h` file.
    -   Replace `"YOUR_WIFI_SSID"` with your Wi-Fi network name.
    -   Replace `"YOUR_WIFI_PASSWORD"` with your Wi-Fi password.
    -   The `GRAPHQL_ENDPOINT` is set to the GitHub API by default. If you are using a different server, change it accordingly.

3.  **Authentication (Optional but Recommended):**
    -   The GitHub GraphQL API has strict rate limits for unauthenticated requests. To make authenticated requests, you need a Personal Access Token.
    -   Uncomment the following line in `basic_query.ino`:
        ```cpp
        // client.setHeader("Authorization", "Bearer YOUR_API_TOKEN");
        ```
    -   Replace `YOUR_API_TOKEN` with your actual GitHub token.

4.  **Upload and Monitor:**
    -   Build and upload the code to your ESP32 board using PlatformIO.
    -   Open the Serial Monitor to see the output. The board will connect to Wi-Fi, execute the query, and print the results.
