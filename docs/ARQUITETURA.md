# Arquitetura do Sistema - Simulação de Ecossistema

## 📐 Visão Geral da Arquitetura

A simulação é construída em uma arquitetura em **camadas** que separa responsabilidades e facilita manutenção:

```
┌─────────────────────────────────────────────────┐
│           Camada de Apresentação                │
│     (Visualização, Logging, Análise)            │
└──────────────────┬──────────────────────────────┘
                   │
┌──────────────────┴──────────────────────────────┐
│         Camada de Aplicação                     │
│   (SimulationEngine, Controladores)             │
└──────────────────┬──────────────────────────────┘
                   │
┌──────────────────┴──────────────────────────────┐
│        Camada de Lógica de Negócios             │
│  (Sistemas: Growth, Building, Resource, Physics)│
└──────────────────┬──────────────────────────────┘
                   │
┌──────────────────┴──────────────────────────────┐
│         Camada de Domínio                       │
│  (Entidades: Plant, Human, Environment)         │
└──────────────────┬──────────────────────────────┘
                   │
┌──────────────────┴──────────────────────────────┐
│         Camada de Dados e Utilidades            │
│    (Estruturas, Constantes, Logger, Math)       │
└─────────────────────────────────────────────────┘
```

---

## 🏛️ Padrões de Design Utilizados

### 1. **Entity Component System (ECS) - Simplificado**
- Entidades são objetos com componentes
- Sistemas operam sobre componentes específicos
- Baixo acoplamento entre entidades

```cpp
// Hierarquia simplificada
Entity (base)
├── Plant
└── Human
```

### 2. **Observer Pattern**
- Ambiente notifica entidades sobre mudanças
- Sistemas observam eventos de simulação
- Desacoplamento entre objetos

### 3. **Singleton Pattern**
- `SimulationEngine`: Controla a simulação global
- `Environment`: Gerencia o mundo (único por execução)
- `ResourceSystem`: Gerencia recursos globais

### 4. **Strategy Pattern**
- Diferentes comportamentos de IA para entidades
- Comportamentos podem ser trocados em runtime
- Facilitam adição de novos tipos de entidades

### 5. **Factory Pattern**
- Criação de entidades controlada
- Consistência na inicialização
- Facilita rastreamento de entidades criadas

---

## 🔄 Fluxo de Dados Principal

```
┌──────────────────┐
│  Início da Sim.  │
└────────┬─────────┘
         │
         ▼
┌──────────────────────────────────────────┐
│  Inicializar Environment & Entities      │
│  - Criar mapa                            │
│  - Adicionar plantas iniciais            │
│  - Adicionar humanos iniciais            │
└────────┬─────────────────────────────────┘
         │
         ▼
┌──────────────────────────────────────────┐
│  Loop Principal de Simulação             │
│                                          │
│  ┌────────────────────────────────────┐  │
│  │ 1. Calcular Tick (Δt)              │  │
│  └────────────────────────────────────┘  │
│  ▼                                       │
│  ┌────────────────────────────────────┐  │
│  │ 2. Physics System                  │  │
│  │    - Detectar colisões             │  │
│  │    - Atualizar posições            │  │
│  └────────────────────────────────────┘  │
│  ▼                                       │
│  ┌────────────────────────────────────┐  │
│  │ 3. Resource System                 │  │
│  │    - Regenerar recursos            │  │
│  │    - Distribuir água, nutrientes   │  │
│  └────────────────────────────────────┘  │
│  ▼                                       │
│  ┌────────────────────────────────────┐  │
│  │ 4. Growth System                   │  │
│  │    - Envelhecimento                │  │ 
│  │    - Reprodução                    │  │
│  │    - Morte natural                 │  │
│  └────────────────────────────────────┘  │
│  ▼                                       │
│  ┌────────────────────────────────────┐  │
│  │ 5. Building System                 │  │
│  │    - Processar construções         │  │
│  │    - Modificar ambiente            │  │
│  └────────────────────────────────────┘  │
│  ▼                                       │
│  ┌────────────────────────────────────┐  │
│  │ 6. Update Entidades                │  │
│  │    - Executar comportamentos       │  │
│  │    - Consumir recursos             │  │
│  │    - Atualizar estado              │  │
│  └────────────────────────────────────┘  │
│  ▼                                       │
│  ┌────────────────────────────────────┐  │
│  │ 7. Renderizar/Logar Estado         │  │
│  └────────────────────────────────────┘  │
└────────┬─────────────────────────────────┘
         │
         ▼
      ┌─────────┐
      │ Simular?│
      └─┬───┬───┘
        │   │
  Não ◄─┘   └─► Sim
      │          │
      ▼          ▼
    ┌─────┐ ┌──────────────────────────┐
    │ Fim │ │ Próximo tick (volta ao 1)│
    └─────┘ └──────────────────────────┘
```

---

## 📦 Componentes Principais

### 1. Environment (Ambiente)

**Responsabilidade:** Gerenciar o mundo da simulação

```cpp
class Environment {
private:
    // Dimensões do mapa
    int width, height;
    
    // Matriz do mundo
    std::vector<std::vector<Cell>> grid;
    
    // Coleção de entidades
    std::vector<std::unique_ptr<Entity>> entities;
    
    // Recursos globais
    float globalWater, globalNutrients;
    
    // Propriedades ambientais
    float temperature, humidity, sunlight;
    
    // Ciclo dia/noite
    int timeOfDay;  // 0-23 horas
    int dayCount;
    
public:
    void initialize(int width, int height);
    void addEntity(std::unique_ptr<Entity> entity);
    void removeEntity(EntityID id);
    Entity* getEntity(EntityID id);
    void updateEnvironment(float deltaTime);
    Cell& getCell(int x, int y);
};
```

---

### 2. Entity (Entidade Base)

**Responsabilidade:** Representar objetos do mundo com propriedades comuns

```cpp
class Entity {
protected:
    EntityID id;
    Vector2D position;
    float age;
    float energy;
    EntityState state;
    
public:
    virtual ~Entity() = default;
    
    virtual void update(float deltaTime, Environment& env) = 0;
    virtual void die() = 0;
    virtual std::string getType() const = 0;
    
    // Getters
    EntityID getId() const { return id; }
    Vector2D getPosition() const { return position; }
    float getEnergy() const { return energy; }
};
```

---

### 3. Plant (Planta)

**Responsabilidade:** Modelar organismos fotossintetizantes

```cpp
class Plant : public Entity {
private:
    float height;
    float rootDepth;
    int age;
    int reproductionAge;
    float nutritionLevel;
    
public:
    void update(float deltaTime, Environment& env) override;
    void photosynthesize(float sunlight);
    void absorbWaterAndNutrients(const Environment& env);
    void grow();
    void reproduce();
    void die() override;
};
```

**Ciclo de vida da planta:**
1. Absorver água e nutrientes do solo
2. Fotossíntese usando luz solar
3. Crescimento gradual
4. Reprodução ao atingir idade mínima
5. Morte ao envelhecer ou falta de recursos

---

### 4. Human (Ser Humano)

**Responsabilidade:** Modelar agentes inteligentes com comportamento autônomo

```cpp
class Human : public Entity {
private:
    std::string name;
    float intelligence;
    float strength;
    HumanBehavior currentBehavior;
    std::vector<ConstructionProject> projects;
    float hunger, thirst;
    
public:
    void update(float deltaTime, Environment& env) override;
    void makeBehaviorDecision(const Environment& env);
    void consumeResources();
    void build();
    void grow();
    void die() override;
    
private:
    void evaluateNeeds();
};
```

**Comportamentos do Humano:**
- Buscar alimento
- Beber água
- Descansar
- Construir estruturas
- Interagir com plantas

---

### 5. SimulationEngine (Motor de Simulação)

**Responsabilidade:** Coordenar toda a lógica de simulação

```cpp
class SimulationEngine {
private:
    static SimulationEngine* instance;
    
    Environment environment;
    std::vector<System*> systems;
    
    float deltaTime;
    int currentTick;
    bool isRunning;
    
    // Callbacks para observadores
    std::vector<SimulationObserver*> observers;
    
public:
    static SimulationEngine* getInstance();
    
    void initialize(int worldWidth, int worldHeight);
    void update();
    void render();
    void stop();
    
    void subscribe(SimulationObserver* observer);
    void notify(const SimulationEvent& event);
};
```

---

### 6. Sistemas Especializados

#### PhysicsSystem
- Detecção de colisões
- Movimento de entidades
- Cálculo de proximidade
- Efeitos da gravidade (se aplicável)

#### ResourceSystem
- Regeneração de água e nutrientes
- Distribuição de recursos
- Gestão de estoque global
- Depleção de recursos

#### GrowthSystem
- Envelhecimento de entidades
- Crescimento proporcional
- Reprodução
- Morte natural

#### BuildingSystem
- Processar projetos de construção
- Validar construções
- Modificar o mapa
- Atualizar custos de recursos

---

## 🔌 Interfaces e Contatos entre Componentes

```
┌─────────────────────────────────────────┐
│       SimulationEngine (Orquestrador)   │
└────┬──────────────────────┬─────────────┘
     │                      │
     ▼                      ▼
┌──────────────┐    ┌──────────────────┐
│ Environment  │───►│ Todos Sistemas   │
│              │    │ (operam sobre)   │
└──────────────┘    └──────────────────┘
     ▲                       ▲
     │                       │
     └──────┬───── ┬─────────┘
            │      │
       ┌─── ▼ ──┐  └──────────┐
       │ Plant  │             │
       └────────┘     ┌────── ▼ ──────┐
                      │    Human      │
                      └────────────── ┘
```

---

## 🎯 Princípios de Design

### 1. **Separação de Responsabilidades**
- Cada classe tem uma única razão para mudar
- Sistemas são independentes e reutilizáveis

### 2. **Baixo Acoplamento**
- Entidades não conhecem detalhes internas dos sistemas
- Comunicação através de interfaces

### 3. **Alta Coesão**
- Métodos relacionados estão no mesmo lugar
- Dados e operações relacionadas juntos

### 4. **Extensibilidade**
- Fácil adicionar novos tipos de entidades
- Fácil adicionar novos sistemas
- Padrão Strategy para comportamentos

### 5. **Testabilidade**
- Componentes podem ser testados isoladamente
- Dependency Injection onde apropriado
- Mocks e stubs possíveis

---

## 📊 Diagrama de Classes (Simplificado)

```
Entity (abstract)
├── Plant
│   ├── - height: float
│   ├── - rootDepth: float
│   └── + photosynthesize(): void
│
└── Human
    ├── - intelligence: float
    ├── - strength: float
    └── + build(): void

Environment
├── - grid: Cell[][]
├── - entities: Entity[]
├── - resources: ResourcePool
└── + updateEnvironment(): void

SimulationEngine (Singleton)
├── - environment: Environment
├── - systems: System[]
└── + update(): void

System (interface)
├── PhysicsSystem
├── ResourceSystem
├── GrowthSystem
└── BuildingSystem
```

---

## 🚀 Fluxo de Inicialização

```
main()
   │
   ▼
SimulationEngine::getInstance()
   │
   ▼
SimulationEngine::initialize()
   │
   ├─► Environment::initialize()
   │   ├─► Criar grid
   │   ├─► Inicializar células
   │   └─► Distribuir recursos iniciais
   │
   ├─► Criar entidades iniciais
   │   ├─► Spawn de plantas
   │   ├─► Spawn de humanos
   │   └─► Posicionar aleatoriamente
   │
   ├─► Registrar sistemas
   │   ├─► PhysicsSystem
   │   ├─► ResourceSystem
   │   ├─► GrowthSystem
   │   └─► BuildingSystem
   │
   └─► Loop de simulação
       └─► SimulationEngine::update() [repetido]
```

---

## 🔐 Considerações de Performance

1. **Estrutura de Dados Eficiente**
   - Grid quadtree para consultas espaciais rápidas
   - Pool de objetos para evitar alocações

2. **Atualizações Parciais**
   - Apenas entidades visíveis/relevantes são atualizadas
   - Batching de operações onde possível

3. **Caching**
   - Cache de células recalculadas
   - Cache de vizinhança

4. **Paralelismo (Futuro)**
   - Sistemas podem executar em paralelo
   - Particionamento do mundo por região

