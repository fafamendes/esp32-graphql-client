[Voltar para a documentação em Português](README.md)

# 🚀 ESP32 GraphQL Client

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A robust and easy-to-use GraphQL client for the ESP32 platform, designed to simplify communication with GraphQL APIs in IoT projects. Inspired by the simplicity and power of Apollo Client, this library makes sending queries and mutations trivial, allowing you to focus on your application's logic, not the complexity of network communication.

## 📜 Table of Contents
* [Introduction](#why-use-this-library)
* [Features](#key-features)
* [Status and Roadmap](#feature-status)
* [Installation and Usage](#installation)
* [Reference API](#reference-api)
* [Examples](#examples)
* [How to Contribute](#how-to-contribute)
* [Read in Portuguese](README.md)

## 🤔 Why use this library?

In an increasingly connected world, IoT devices need to communicate with cloud services efficiently. GraphQL stands out as a powerful alternative to traditional REST APIs, allowing the client to request exactly the data it needs. This library was created to fill the gap of a complete and easy-to-use GraphQL client in the ESP32 ecosystem.

**Common Use Cases:**

- **Remote Monitoring:** Send sensor data (temperature, humidity, etc.) from an ESP32 to a real-time dashboard.
- **Device Control:** Receive commands from a server to control actuators (relays, motors, lights) connected to the ESP32.
- **Secure Authentication:** Use authorization headers to communicate with protected GraphQL APIs.
- **Home Automation Projects:** Integrate your ESP32 devices into a home automation system that uses GraphQL.

## 📣 Announcement: Nest.js API Example Coming Soon!

To further facilitate development and testing, we are preparing an example repository with a complete GraphQL API built with **Nest.js**. This example will serve as a reference backend for you to test your integrations with the `esp32-graphql-client`.

Keep an eye on this repository for more news!

## ✨ Key Features

- **Queries and Mutations:** Full support for fundamental GraphQL operations.
- **Configurable HTTP Client:** Define your server endpoint simply and directly.
- **Custom Headers:** Add HTTP headers for authentication, such as `Authorization: Bearer ...`, or any other necessary metadata.
- **Error Handling:** Differentiates and reports network errors (connection failure) from GraphQL errors (returned in the `errors` array of the response).
- **Lightweight and Efficient:** Built with a focus on performance and low memory consumption, using `ArduinoJson` for parsing and serialization.

## 🚦 Feature Status

This section details the current status of the library's features:

- ✅ **Queries:** Fully supported.
- ✅ **Mutations:** Fully supported.
- ✅ **Custom Headers:** Fully supported.
- ✅ **Error Handling:** Fully supported.
- 🟡 **File Uploads:** Not natively supported. The library does not handle `multipart/form-data` requests. It can be implemented manually with the ESP32 `HTTPClient` library, but would require manual handling of the request body and headers.
- ❌ **Subscriptions:** Not supported (requires WebSockets).
- ❌ **In-Memory Cache:** Not supported.
- ❌ **Persisted Queries:** Not supported.

## 🗺️ Roadmap

- [ ] Support for GraphQL Subscriptions via WebSockets.
- [ ] Implementation of an in-memory cache for queries.
- [ ] Support for persisted queries.

## 📦 Installation

The easiest way to install this library is through the PlatformIO library manager.

Add the following line to the `lib_deps` section of your `platformio.ini` file:

```ini
lib_deps =
    https://github.com/fafamendes/esp32-graphql-client.git
```

PlatformIO will clone this repository and automatically install the library and its dependencies (`ArduinoJson`).

## 🚀 Getting Started

To use the library in your project, follow these steps:

1.  **Include the library:**

    ```cpp
    #include <GraphQLClient.h>
    ```

2.  **Instantiate the client with your server endpoint:**

    ```cpp
    GraphQLClient client("https://countries.trevorblades.com/"); // Example with a public API
    ```

3.  **Execute a query:**

    ```cpp
    void loop() {
      // 1. Define the query and variables
      const char* getCountryQuery = R"(
        query GetCountry($code: ID!) {
          country(code: $code) {
            name
            capital
            currency
          }
        }
      )";
      
      JsonDocument variables;
      variables["code"] = "BR"; // Country code (Brazil)

      // 2. Execute a query
      GraphQLResponse response = client.query(getCountryQuery, variables);

      // 3. Use the data
      if (!response.error) {
        const char* countryName = response.data["data"]["country"]["name"];
        Serial.print("Country Name: ");
        Serial.println(countryName);
      } else {
        Serial.print("Request Error: ");
        Serial.println(response.errorMessage);
      }

      delay(60000);
    }
    ```

## 📚 Reference API

### `GraphQLClient(const char* endpoint)`

Creates a new instance of the GraphQL client.

- **`endpoint`**: The URL of your GraphQL server.

### `void setHeader(const char* key, const char* value)`

Adds a custom HTTP header to all requests.

- **`key`**: The header key (e.g., `