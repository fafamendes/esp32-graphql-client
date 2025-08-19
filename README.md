[Leia em Português](README.pt.md)

# 🚀 ESP32 GraphQL Client

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A robust and easy-to-use GraphQL client for the ESP32 platform, designed to simplify communication with GraphQL APIs in IoT projects. Inspired by the simplicity and power of Apollo Client, this library makes sending queries and mutations trivial, allowing you to focus on your application's logic, not the complexity of network communication.

## 📜 Table of Contents
* [Introduction](#why-use-this-library)
* [Features](#-features)
* [Installation](#installation)
* [Getting Started](#getting-started)
* [Reference API](#reference-api)
* [Examples](#examples)
* [How to Contribute](#how-to-contribute)
* [Acknowledgements](#acknowledgements)
* [License](#license)

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

## ✨ Features

| Status | Feature | Notes |
| :---: | :--- | :--- |
| ✅ | Queries & Mutations | Fully supported. |
| ✅ | Custom Headers | Fully supported. |
| ✅ | Error Handling | Differentiates between network and GraphQL errors. |
| 🟡 | File Uploads | Not natively supported. Requires manual implementation. |
| 🔵 | Subscriptions | **Planned:** Support via WebSockets is on the roadmap. |
| 🔵 | In-Memory Cache | **Planned:** Optional caching for queries. |
| 🔵 | Persisted Queries | **Planned:** Support for persisted queries. |

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
      // 1. Define the query string
      const char* getCountryQuery = R"(
        query GetCountry($code: ID!) {
          country(code: $code) {
            name
            capital
            currency
          }
        }
      )";
      
      // 2. Create a StaticJsonDocument for the variables.
      // Using StaticJsonDocument is highly recommended to avoid memory fragmentation.
      StaticJsonDocument<100> variables;
      variables["code"] = "BR"; // Country code (Brazil)

      // 3. Execute the query
      GraphQLResponse response = client.query(getCountryQuery, variables.as<JsonObject>());

      // 4. Process the response
      // IMPORTANT: The data in the 'response' object is temporary and will be
      // cleared on the next request. Copy any values you need to keep.
      if (!response.hasError) {
        // Safely copy the data you need
        const char* countryName = response.data["country"]["name"];
        String capital = response.data["country"]["capital"].as<String>();

        Serial.print("Country Name: ");
        Serial.println(countryName);
        Serial.print("Capital: ");
        Serial.println(capital);
      } else {
        Serial.print("Error: ");
        Serial.println(response.getErrorMessage());
      }

      delay(60000);
    }
    ```

## 📚 Reference API

### `GraphQLClient(const char* endpoint)`

Creates a new instance of the GraphQL client.

- **`endpoint`**: The URL of your GraphQL server.

### `void setHeader(const char* key, const char* value)`

Adds a custom HTTP header to all requests. Useful for authentication.

- **`key`**: The header key (e.g., `"Authorization"`).
- **`value`**: The header value (e.g., `"Bearer YOUR_TOKEN"`).

### `GraphQLResponse query(const char* query, JsonObject variables)`

Executes a GraphQL query.

- **`query`**: The GraphQL query string.
- **`variables`**: A `JsonObject` from an `ArduinoJson` document containing the query variables.

### `GraphQLResponse mutate(const char* mutation, JsonObject variables)`

Executes a GraphQL mutation.

- **`mutation`**: The GraphQL mutation string.
- **`variables`**: A `JsonObject` from an `ArduinoJson` document containing the mutation variables.

### `GraphQLResponse`

A struct that contains the response from the request.

- **`const JsonObject data`**: A read-only JSON object with the `data` field from the response.
- **`const JsonArray errors`**: A read-only JSON array with the `errors` field from the response.
- **`bool hasError`**: `true` if the `errors` array is not empty.
- **`String getErrorMessage()`**: Returns a formatted string of all error messages.

> ⚠️ **Important:** The `data` and `errors` fields are views into a temporary internal buffer. Their content is only valid until the next request is made. If you need to store data from the response, **you must copy it** to your own variables immediately after receiving the response.

## 📂 Examples

You can find usage examples in the `examples` folder.

## 🙏 Acknowledgements

This project uses the fantastic [ArduinoJson](https://arduinojson.org/) library by Benoît Blanchon for JSON parsing and serialization. A special thanks to the author for his excellent work and for making working with JSON on microcontrollers so efficient.

We also thank the community and developers of the [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) for providing a robust and feature-rich platform for embedded application development.

## 🛠️ How to Contribute

If you want to contribute to the development of this library, follow these steps:

### 1. Clone the Repository

```bash
git clone https://github.com/fafamendes/esp32-graphql-client.git
cd esp32-graphql-client
```

### 2. Create a `main.cpp` for Testing

Since `src/main.cpp` is not part of the repository, you can create your own to test your modifications. Create a `src/main.cpp` file with the following content:

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include "GraphQLClient.h"

// --- Wi-Fi Settings ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// --- GraphQL Client Settings ---
GraphQLClient client("http://your-server.com/graphql");

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("
WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your test code here
}
```

**Important:** Remember that `src/main.cpp` will not be pushed to Git, as it is in the `.gitignore` file.

### 3. Make Your Changes

Now you can modify the library files (`src/GraphQLClient.cpp` and `include/GraphQLClient.h`) and test them using your `main.cpp`.

### 4. Submit a Pull Request

After making your changes and testing them, submit a Pull Request so we can review and integrate your contributions.

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
