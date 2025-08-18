# 🚀 ESP32 GraphQL Client

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Um cliente GraphQL robusto e de fácil utilização para a plataforma ESP32, projetado para simplificar a comunicação com APIs GraphQL em projetos de IoT. Inspirado na simplicidade e poder do Apollo Client, esta biblioteca torna trivial a tarefa de enviar queries e mutations, permitindo que você se concentre na lógica do seu aplicativo, e não na complexidade da comunicação de rede.

## 🤔 Por que usar esta biblioteca?

Em um mundo cada vez mais conectado, dispositivos IoT precisam se comunicar com serviços na nuvem de forma eficiente. GraphQL se destaca como uma alternativa poderosa às APIs REST tradicionais, permitindo que o cliente solicite exatamente os dados de que precisa. Esta biblioteca foi criada para preencher a lacuna de um cliente GraphQL completo e fácil de usar no ecossistema do ESP32.

**Casos de Uso Comuns:**

- **Monitoramento Remoto:** Enviar dados de sensores (temperatura, umidade, etc.) de um ESP32 para um dashboard em tempo real.
- **Controle de Dispositivos:** Receber comandos de um servidor para controlar atuadores (relés, motores, luzes) conectados ao ESP32.
- **Autenticação Segura:** Utilizar cabeçalhos de autorização para se comunicar com APIs GraphQL protegidas.
- **Projetos de Automação Residencial:** Integrar seus dispositivos ESP32 a um sistema de automação residencial que utiliza GraphQL.

## 📣 Anúncio: Exemplo de API em Nest.js em Breve!

Para facilitar ainda mais o desenvolvimento e os testes, estamos preparando um repositório de exemplo com uma API GraphQL completa construída com **Nest.js**. Este exemplo servirá como um backend de referência para você testar suas integrações com o `esp32-graphql-client`.

Fique de olho neste repositório para mais novidades!

## ✨ Funcionalidades Principais

- **Queries e Mutations:** Suporte completo para as operações fundamentais do GraphQL.
- **Cliente HTTP Configurável:** Defina o endpoint do seu servidor de forma simples e direta.
- **Cabeçalhos Customizados:** Adicione cabeçalhos HTTP para autenticação, como `Authorization: Bearer ...`, ou qualquer outro metadado necessário.
- **Tratamento de Erros:** Diferencia e reporta erros de rede (falha na conexão) de erros do GraphQL (retornados no array `errors` da resposta).
- **Leve e Eficiente:** Construído com foco em performance e baixo consumo de memória, utilizando `ArduinoJson` para parsing e serialização.

## 🚦 Status das Funcionalidades

Esta seção detalha o estado atual das funcionalidades da biblioteca:

- ✅ **Queries:** Totalmente suportado.
- ✅ **Mutations:** Totalmente suportado.
- ✅ **Cabeçalhos Customizados:** Totalmente suportado.
- ✅ **Tratamento de Erros:** Totalmente suportado.
- 🟡 **Upload de Arquivos:** Não suportado nativamente. A biblioteca não lida com requisições `multipart/form-data`. Pode ser implementado manualmente com a biblioteca `HTTPClient` do ESP32, mas exigiria manipulação manual do corpo da requisição e dos cabeçalhos.
- ❌ **Subscriptions:** Não suportado (requer WebSockets).
- ❌ **Cache em Memória:** Não suportado.
- ❌ **Queries Persistidas:** Não suportado.

## 🗺️ Roadmap

- [ ] Suporte a Subscriptions GraphQL via WebSockets.
- [ ] Implementação de um cache em memória para queries.
- [ ] Suporte a queries persistidas.

## 📦 Instalação

A maneira mais fácil de instalar esta biblioteca é através do gerenciador de bibliotecas do PlatformIO.

Adicione a seguinte linha à seção `lib_deps` do seu arquivo `platformio.ini`:

```ini
lib_deps =
    https://github.com/fafamendes/esp32-graphql-client.git
```

O PlatformIO irá clonar este repositório e instalar a biblioteca e suas dependências (`ArduinoJson`) automaticamente.

## 🚀 Como Começar

Para usar a biblioteca em seu projeto, siga estes passos:

1.  **Inclua a biblioteca:**

    ```cpp
    #include <GraphQLClient.h>
    ```

2.  **Instancie o cliente com o endpoint do seu servidor:**

    ```cpp
    GraphQLClient client("https://countries.trevorblades.com/"); // Exemplo com uma API pública
    ```

3.  **Execute uma query:**

    ```cpp
    void loop() {
      // 1. Defina a query e as variáveis
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
      variables["code"] = "BR"; // Código do país (Brasil)

      // 2. Execute a query
      GraphQLResponse response = client.query(getCountryQuery, variables);

      // 3. Use os dados
      if (!response.error) {
        const char* countryName = response.data["data"]["country"]["name"];
        Serial.print("Nome do país: ");
        Serial.println(countryName);
      } else {
        Serial.print("Erro na requisição: ");
        Serial.println(response.errorMessage);
      }

      delay(60000);
    }
    ```

## 📚 API de Referência

### `GraphQLClient(const char* endpoint)`

Cria uma nova instância do cliente GraphQL.

- **`endpoint`**: O URL do seu servidor GraphQL.

### `void setHeader(const char* key, const char* value)`

Adiciona um cabeçalho HTTP customizado a todas as requisições.

- **`key`**: A chave do cabeçalho (ex: `"Authorization"`).
- **`value`**: O valor do cabeçalho (ex: `"Bearer SEU_TOKEN"`).

### `GraphQLResponse query(const char* query, JsonDocument& variables)`

Executa uma query GraphQL.

- **`query`**: A string da query GraphQL.
- **`variables`**: Um `JsonDocument` do ArduinoJson com as variáveis da query.

### `GraphQLResponse mutation(const char* mutation, JsonDocument& variables)`

Executa uma mutation GraphQL.

- **`mutation`**: A string da mutation GraphQL.
- **`variables`**: Um `JsonDocument` do ArduinoJson com as variáveis da mutation.

### `GraphQLResponse`

Um struct que contém a resposta da requisição.

- **`bool error`**: `true` se ocorreu um erro.
- **`String errorMessage`**: A mensagem de erro, se houver.
- **`JsonDocument data`**: Os dados da resposta em um `JsonDocument`.
- **`int httpCode`**: O código de status HTTP da requisição.

## 📂 Exemplos

Você pode encontrar exemplos de uso na pasta `examples`:

- **`basic_query`**: Um exemplo simples d
## Agradecimentos

Este projeto utiliza a fantástica biblioteca [ArduinoJson](https://arduinojson.org/) de Benoît Blanchon para o parse e serialização de JSON. Um agradecimento especial ao autor por seu excelente trabalho e por tornar o trabalho com JSON em microcontroladores tão eficiente.

Agradecemos também à comunidade e aos desenvolvedores do [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) por fornecerem uma plataforma robusta e rica em recursos para o desenvolvimento de aplicações embarcadas.

## 🛠️ Como Contribuir

Se você deseja contribuir para o desenvolvimento desta biblioteca, siga estes passos:

### 1. Clone o Repositório

```bash
git clone https://github.com/fafamendes/esp32-graphql-client.git
cd esp32-graphql-client
```

### 2. Crie um `main.cpp` para Testes

Como o `src/main.cpp` não faz parte do repositório, você pode criar o seu próprio para testar suas modificações. Crie um arquivo `src/main.cpp` com o seguinte conteúdo:

```cpp
#include <Arduino.h>
#include <WiFi.h>
#include "GraphQLClient.h"

// --- Configurações de Wi-Fi ---
const char* ssid = "SEU_WIFI_SSID";
const char* password = "SUA_WIFI_SENHA";

// --- Configurações do Cliente GraphQL ---
GraphQLClient client("http://seu-servidor.com/graphql");

void setup() {
  Serial.begin(115200);
  delay(100);

  // Conectar ao Wi-Fi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Seu código de teste aqui
}
```

**Importante:** Lembre-se de que o `src/main.cpp` não será enviado para o Git, pois está no `.gitignore`.

### 3. Faça suas Alterações

Agora você pode modificar os arquivos da biblioteca (`src/GraphQLClient.cpp` e `include/GraphQLClient.h`) e testá-los usando o seu `main.cpp`.

### 4. Envie um Pull Request

Depois de fazer suas alterações e testá-las, envie um Pull Request para que possamos revisar e integrar suas contribuições.

## 📄 Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

---

# 🚀 ESP32 GraphQL Client

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A robust and easy-to-use GraphQL client for the ESP32 platform, designed to simplify communication with GraphQL APIs in IoT projects. Inspired by the simplicity and power of Apollo Client, this library makes sending queries and mutations trivial, allowing you to focus on your application's logic, not the complexity of network communication.

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

      // 2. Execute the query
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

- **`key`**: The header key (e.g., `"Authorization"`).
- **`value`**: The header value (e.g., `"Bearer YOUR_TOKEN"`).

### `GraphQLResponse query(const char* query, JsonDocument& variables)`

Executes a GraphQL query.

- **`query`**: The GraphQL query string.
- **`variables`**: An ArduinoJson `JsonDocument` with the query variables.

### `GraphQLResponse mutation(const char* mutation, JsonDocument& variables)`

Executes a GraphQL mutation.

- **`mutation`**: The GraphQL mutation string.
- **`variables`**: An ArduinoJson `JsonDocument` with the mutation variables.

### `GraphQLResponse`

A struct containing the response of the request.

- **`bool error`**: `true` if an error occurred.
- **`String errorMessage`**: The error message, if any.
- **`JsonDocument data`**: The response data in a `JsonDocument`.
- **`int httpCode`**: The HTTP status code of the request.

## 📂 Examples

You can find usage examples in the `examples` folder:

- **`basic_query`**: A simple example of how to execute a query.
- **`send_esp32_stats`**: A more complex example that sends ESP32 statistics to a GraphQL server using a mutation.

## Acknowledgements

This project utilizes the fantastic [ArduinoJson](https://arduinojson.org/) library by Benoît Blanchon for JSON parsing and serialization. Special thanks to the author for his excellent work and for making JSON handling on microcontrollers so efficient.

We also thank the community and developers of the [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) for providing a robust and feature-rich platform for embedded application development.

## 🛠️ How to Contribute

If you wish to contribute to the development of this library, follow these steps:

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
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Your test code here
}
```

**Important:** Remember that `src/main.cpp` will not be pushed to Git, as it is in `.gitignore`.

### 3. Make your Changes

Now you can modify the library files (`src/GraphQLClient.cpp` and `include/GraphQLClient.h`) and test them using your `main.cpp`.

### 4. Submit a Pull Request

After making your changes and testing them, submit a Pull Request so we can review and integrate your contributions.

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.rações e testá-las, envie um Pull Request para que possamos revisar e integrar suas contribuições.

## 📄 Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.