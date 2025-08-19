[Read in English](README.md)

# 🚀 ESP32 GraphQL Client

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Um cliente GraphQL robusto e de fácil utilização para a plataforma ESP32, projetado para simplificar a comunicação com APIs GraphQL em projetos de IoT. Inspirado na simplicidade e poder do Apollo Client, esta biblioteca torna trivial a tarefa de enviar queries e mutations, permitindo que você se concentre na lógica do seu aplicativo, e não na complexidade da comunicação de rede.

## 📜 Índice
* [Introdução](#por-que-usar-esta-biblioteca)
* [Funcionalidades](#-funcionalidades)
* [Instalação](#instalação)
* [Como Começar](#como-começar)
* [API de Referência](#api-de-referência)
* [Exemplos](#exemplos)
* [Como Contribuir](#como-contribuir)
* [Agradecimentos](#agradecimentos)
* [Licença](#licença)

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

## ✨ Funcionalidades

| Status | Funcionalidade | Notas |
| :---: | :--- | :--- |
| ✅ | Queries & Mutations | Totalmente suportado. |
| ✅ | Cabeçalhos Customizados | Totalmente suportado. |
| ✅ | Tratamento de Erros | Diferencia erros de rede e erros do GraphQL. |
| 🟡 | Upload de Arquivos | Não suportado nativamente. Requer implementação manual. |
| 🔵 | Subscriptions | **Planejado:** Suporte via WebSockets está no roadmap. |
| 🔵 | Cache em Memória | **Planejado:** Cache opcional para queries. |
| 🔵 | Queries Persistidas | **Planejado:** Suporte para queries persistidas. |

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
      // 1. Defina a string da query
      const char* getCountryQuery = R"(
        query GetCountry($code: ID!) {
          country(code: $code) {
            name
            capital
            currency
          }
        }
      )";
      
      // 2. Crie um StaticJsonDocument para as variáveis.
      // Usar StaticJsonDocument é altamente recomendado para evitar fragmentação da memória.
      StaticJsonDocument<100> variaveis;
      variaveis["code"] = "BR"; // Código do país (Brasil)

      // 3. Execute a query
      GraphQLResponse response = client.query(getCountryQuery, variaveis.as<JsonObject>());

      // 4. Processe a resposta
      // IMPORTANTE: Os dados no objeto 'response' são temporários e serão
      // limpos na próxima requisição. Copie os valores que você precisa manter.
      if (!response.hasError) {
        // Copie com segurança os dados que você precisa
        const char* nomePais = response.data["country"]["name"];
        String capital = response.data["country"]["capital"].as<String>();

        Serial.print("Nome do País: ");
        Serial.println(nomePais);
        Serial.print("Capital: ");
        Serial.println(capital);
      } else {
        Serial.print("Erro: ");
        Serial.println(response.getErrorMessage());
      }

      delay(60000);
    }
    ```

## 📚 API de Referência

### `GraphQLClient(const char* endpoint)`

Cria uma nova instância do cliente GraphQL.

- **`endpoint`**: O URL do seu servidor GraphQL.

### `void setHeader(const char* key, const char* value)`

Adiciona um cabeçalho HTTP customizado a todas as requisições. Útil para autenticação.

- **`key`**: A chave do cabeçalho (ex: `"Authorization"`).
- **`value`**: O valor do cabeçalho (ex: `"Bearer SEU_TOKEN"`).

### `GraphQLResponse query(const char* query, JsonObject variables)`

Executa uma query GraphQL.

- **`query`**: A string da query GraphQL.
- **`variables`**: Um `JsonObject` de um documento `ArduinoJson` contendo as variáveis da query.

### `GraphQLResponse mutate(const char* mutation, JsonObject variables)`

Executa uma mutation GraphQL.

- **`mutation`**: A string da mutation GraphQL.
- **`variables`**: Um `JsonObject` de um documento `ArduinoJson` contendo as variáveis da mutação.

### `GraphQLResponse`

Um struct que contém a resposta da requisição.

- **`const JsonObject data`**: Um objeto JSON somente leitura com o campo `data` da resposta.
- **`const JsonArray errors`**: Um array JSON somente leitura com o campo `errors` da resposta.
- **`bool hasError`**: `true` se o array `errors` não estiver vazio.
- **`String getErrorMessage()`**: Retorna uma string formatada com todas as mensagens de erro.

> ⚠️ **Importante:** Os campos `data` e `errors` são visualizações de um buffer interno temporário. O conteúdo deles é válido apenas até a próxima requisição ser feita. Se você precisa armazenar dados da resposta, **você deve copiá-los** para suas próprias variáveis imediatamente após receber a resposta.

## 📂 Exemplos

Você pode encontrar exemplos de uso na pasta `examples`.

## 🙏 Agradecimentos

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
