# Guia de Desenvolvimento - Simulação de Ecossistema

## 👨‍💻 Bem-vindo ao Desenvolvimento!

Este guia ajuda novos desenvolvedores a entender como contribuir ao projeto. Ele cobre padrões de código, workflow, boas práticas e processo de desenvolvimento.

---

## 📦 Ambiente de Desenvolvimento

### Pré-requisitos

- **Compilador:** GCC 8+, Clang 10+ ou MSVC 2019+
- **CMake:** 3.15 ou superior
- **Git:** 2.0 ou superior
- **Editor:** VS Code, CLion, Visual Studio ou similar

### Setup Inicial

1. **Clone o repositório:**
```bash
git clone <repo-url>
cd asistente
```

2. **Crie o build directory:**
```bash
mkdir build
cd build
```

3. **Configure com CMake:**
```bash
cmake ..
```

4. **Compile:**
```bash
make -j$(nproc)
```

5. **Teste a compilação:**
```bash
./ecosystem
```

---

## 🎨 Padrões de Código

### 1. Nomenclatura

**Arquivos:**
- Headers: `PascalCase.h`
- Source: `PascalCase.cpp`
- Exemplo: `SimulationEngine.h`, `SimulationEngine.cpp`

**Classes e Structs:**
- PascalCase
- Exemplo: `class SimulationEngine`, `struct Vector2D`

**Métodos e Funções:**
- camelCase
- Exemplo: `void updatePosition()`, `float getEnergy()`

**Variáveis:**
- camelCase
- Constantes: UPPER_SNAKE_CASE
- Exemplo: `float currentEnergy`, `const float MAX_ENERGY = 100.0f`

**Enums:**
- PascalCase para enum class, UPPER_SNAKE_CASE para valores
- Exemplo:
```cpp
enum class EntityState {
    ALIVE = 0,
    DEAD = 1
};
```

### 2. Estrutura de Classe

```cpp
class ExampleClass {
public:
    // Construtores
    ExampleClass();
    ExampleClass(float param1, int param2);
    ~ExampleClass();
    
    // Métodos públicos
    void doSomething();
    float getSomething() const;
    void setSomething(float value);
    
protected:
    // Métodos protegidos
    void protectedMethod();
    
private:
    // Membros privados
    float member1;
    int member2;
    
    // Métodos privados
    void helperMethod();
};
```

### 3. Documentação de Código

Use comentários **apenas** onde a intenção não é óbvia:

```cpp
// ❌ Ruim - obvio
float energy = 0.0f;  // energia = 0

// ✅ Bom - explica por quê
if (hungerLevel > 80) {
    // Humano muito faminto, quer comida imediatamente
    primaryNeed = HumanNeed::HUNGER;
}
```

**Docstrings para métodos públicos:**

```cpp
/**
 * Calcula a eficiência de trabalho do humano.
 * 
 * Considera fome, sede, cansaço e atributos físicos.
 * Retorna valor entre 0 e 1 onde:
 *   0 = incapacitado
 *   1 = máxima eficiência
 * 
 * @return float Eficiência de trabalho [0, 1]
 */
float getWorkEfficiency() const;
```

### 4. Includes

Organize includes em ordem:

```cpp
// Padrão C++
#include <vector>
#include <map>
#include <memory>

// Bibliotecas externas
#include <rapidjson/document.h>

// Projeto (relative ao src/)
#include "core/Environment.h"
#include "entities/Entity.h"
#include "utils/Vector2D.h"
```

### 5. Formatação

**Espaçamento:**
```cpp
// ✅ Bom
for (int i = 0; i < 10; ++i) {
    doSomething();
}

if (condition) {
    // código
}

class MyClass {
private:
    float member;
    
public:
    void method() { }
};

// ❌ Ruim
for(int i=0;i<10;++i){doSomething();}
```

**Comprimento de Linha:**
- Máximo: 100 caracteres
- Se linha fica muito longa, divida:

```cpp
// ✅ Bom
float efficiency = 
    (strength / 10.0f) * 
    (intelligence / 10.0f) * 
    hungerFactor;

// ❌ Ruim
float efficiency = (strength / 10.0f) * (intelligence / 10.0f) * hungerFactor;
```

---

## 🔄 Workflow de Desenvolvimento

### Branch Strategy

1. **main:** Versão estável (produção)
2. **develop:** Integração (pré-produção)
3. **feature/XXX:** Features novas
4. **bugfix/XXX:** Correções de bugs
5. **docs/XXX:** Documentação

### Processo de Contribuição

1. **Crie uma branch:**
```bash
git checkout develop
git pull origin develop
git checkout -b feature/nova-mecanica
```

2. **Desenvolva sua feature:**
```bash
# ... edite arquivos ...
git add .
git commit -m "feat: adicionar nova mecânica de crescimento"
```

3. **Mantenha sincronizado com develop:**
```bash
git fetch origin
git rebase origin/develop
```

4. **Push para seu fork:**
```bash
git push origin feature/nova-mecanica
```

5. **Abra Pull Request:**
- Descreva a mudança
- Referencie issues relacionadas
- Solicite revisão

### Formato de Commit

Use convenção [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Tipos:**
- `feat`: Nova feature
- `fix`: Correção de bug
- `docs`: Documentação
- `refactor`: Refatoração
- `test`: Testes
- `perf`: Performance

**Exemplos:**
```
feat(plant): adicionar fotossíntese com ciclo dia-noite

fix(human): corrigir cálculo de fome quando come

docs(mecanicas): atualizar fórmulas de crescimento

refactor(entities): extrair classe base comum para seres vivos

test(growth): adicionar testes para sistema de crescimento
```

---

## 🧪 Testes

### Estrutura de Testes

```cpp
// tests/test_environment.cpp
#include <gtest/gtest.h>
#include "core/Environment.h"

class EnvironmentTest : public ::testing::Test {
protected:
    Environment env;
    
    void SetUp() override {
        env.initialize(100, 100);
    }
};

TEST_F(EnvironmentTest, InitialWaterLevel) {
    EXPECT_GT(env.getWaterLevel(), 0.0f);
}

TEST_F(EnvironmentTest, AddEntity) {
    auto plant = std::make_unique<Plant>(PlantType::TREE, Vector2D(50, 50));
    EntityID id = plant->getId();
    env.addEntity(std::move(plant));
    
    EXPECT_NE(env.getEntity(id), nullptr);
}
```

### Rodando Testes

```bash
cd build
make test
# ou
ctest --verbose
```

### Cobertura

```bash
# Compilar com coverage
cmake .. -DCMAKE_BUILD_TYPE=Coverage
make coverage
```

---

## 🐛 Debugging

### Compilação com Debug

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

### Usando GDB

```bash
gdb ./ecosystem
(gdb) break SimulationEngine::update
(gdb) run
(gdb) step
(gdb) print variable
(gdb) continue
(gdb) quit
```

### Usando Valgrind (Memory Leak Detection)

```bash
valgrind --leak-check=full ./ecosystem
```

### Logging

```cpp
#include "utils/Logger.h"

Logger::debug("Debug message: {}", value);
Logger::info("Info message");
Logger::warning("Warning!");
Logger::error("Error occurred");
```

---

## 📈 Performance

### Profiling

```bash
# Usando perf (Linux)
perf record ./ecosystem
perf report

# Usando gprof
g++ -pg -o ecosystem src/*.cpp
./ecosystem
gprof ecosystem gmon.out | head -20
```

### Otimizações Comuns

1. **Cache de cálculos frequentes:**
```cpp
// ❌ Ruim - recalcula todo tick
float efficiency = calculateEfficiency();

// ✅ Bom - cache
float efficiency;
bool needsRecalc = true;

void update() {
    if (needsRecalc) {
        efficiency = calculateEfficiency();
        needsRecalc = false;
    }
}
```

2. **Use move semantics:**
```cpp
// ❌ Ruim
void addEntity(Entity entity) { }

// ✅ Bom
void addEntity(Entity&& entity) { }
// ou
void addEntity(std::unique_ptr<Entity> entity) { }
```

3. **Evite cópias desnecessárias:**
```cpp
// ❌ Ruim
for (const auto entity : allEntities) { }

// ✅ Bom
for (const auto& entity : allEntities) { }
```

---

## 📚 Recursos para Desenvolvedores

### Documentação Interna

- [ARQUITETURA.md](./ARQUITETURA.md) - Arquitetura do sistema
- [ENTITIES.md](./ENTITIES.md) - Entidades e seus comportamentos
- [MECANICAS.md](./MECANICAS.md) - Regras de simulação
- [ESPECIFICACOES.md](./ESPECIFICACOES.md) - APIs e estruturas

### Links Externos

- [C++ Reference](https://en.cppreference.com/)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [CMake Documentation](https://cmake.org/documentation/)

---

## 🎯 Tarefas Comuns

### Adicionar Nova Propriedade a Entidade

1. **Adicione membro à classe:**
```cpp
class Plant : public Entity {
private:
    float newProperty;
};
```

2. **Adicione getter/setter:**
```cpp
float getNewProperty() const { return newProperty; }
void setNewProperty(float value) { newProperty = value; }
```

3. **Atualize em update():**
```cpp
void update(float deltaTime, Environment& env) override {
    // ... outras lógicas ...
    newProperty += deltaTime * rate;
}
```

4. **Teste a mudança:**
```cpp
TEST_F(PlantTest, NewPropertyIncreases) {
    Plant plant(PlantType::TREE, Vector2D(0, 0));
    float initial = plant.getNewProperty();
    // ... simulação ...
    EXPECT_GT(plant.getNewProperty(), initial);
}
```

### Adicionar Novo Tipo de Planta

1. **Adicione ao enum:**
```cpp
enum class PlantType {
    // ... existentes ...
    NEW_PLANT = 5
};
```

2. **Crie constantes:**
```cpp
namespace PlantConstants {
    namespace NewPlant {
        constexpr float MAX_HEIGHT = 2.0f;
        constexpr int MAX_AGE = 1000;
        constexpr float PHOTOSYNTHESIS_RATE = 1.5f;
        // ...
    }
}
```

3. **Atualize Plant::update():**
```cpp
void Plant::update(float deltaTime, Environment& env) {
    switch (type) {
        case PlantType::NEW_PLANT:
            // lógica específica
            break;
        // ...
    }
}
```

4. **Teste:**
```cpp
TEST(PlantTest, NewPlantGrowsCorrectly) {
    Plant newPlant(PlantType::NEW_PLANT, Vector2D(0, 0));
    // ... verificar crescimento ...
}
```

### Adicionar Novo Sistema

1. **Crie header:**
```cpp
// src/systems/NewSystem.h
class NewSystem : public System {
public:
    void update(Environment& env, float deltaTime) override;
    // ...
};
```

2. **Implemente:**
```cpp
// src/systems/NewSystem.cpp
void NewSystem::update(Environment& env, float deltaTime) {
    // lógica
}
```

3. **Registre no engine:**
```cpp
void SimulationEngine::initialize(SimulationConfig config) {
    // ...
    systems.push_back(std::make_unique<NewSystem>());
}
```

---

## ✅ Checklist Antes de Submeter PR

- [ ] Código segue padrões de nomenclatura
- [ ] Código formatado corretamente (sem linhas > 100 caracteres)
- [ ] Testes adicionados e passando
- [ ] Documentação atualizada
- [ ] Commits com mensagens claras
- [ ] Sem warnings de compilação
- [ ] Sem memory leaks (valgrind)
- [ ] Performance não degradada

---

## 🚀 Roadmap de Desenvolvimento

### Fase 1: Fundação ✅
- [x] Arquitetura definida
- [x] Documentação completa
- [x] Setup inicial

### Fase 2: Core Implementation 🔄
- [ ] Implementar classes base (Entity, Environment)
- [ ] Implementar Plant e ciclo de vida
- [ ] Implementar Human e comportamentos
- [ ] Implementar SimulationEngine
- [ ] Implementar sistemas básicos

### Fase 3: Features Avançadas
- [ ] Sistema de IA melhorado
- [ ] Colaboração entre humanos
- [ ] Construções persistentes
- [ ] Salvamento/Carregamento
- [ ] Visualização gráfica

### Fase 4: Polish
- [ ] Otimização de performance
- [ ] Testes extensivos
- [ ] Documentação de API
- [ ] Release 1.0

---

## 📞 Contato e Dúvidas

- **Issues:** Use GitHub Issues para relatar bugs ou sugerir features
- **Discussions:** Use GitHub Discussions para dúvidas e discussões
- **Email:** markus@example.com

---

## 📝 Licença

Todos os contribuidores concordam que suas contribuições são licenciadas sob MIT License.

