# Documentação de Entidades - Simulação de Ecossistema

## 📋 Visão Geral

Entidades são os objetos principais que existem no mundo da simulação. Existem dois tipos principais: **Plantas** e **Humanos**. Ambas herdam de uma classe base `Entity`.

---

## 🌍 Classe Base: Entity

### Definição

```cpp
class Entity {
protected:
    EntityID id;                    // Identificador único
    Vector2D position;              // Posição no mundo
    float age;                      // Idade em ticks
    float energy;                   // Energia atual
    EntityState state;              // Estado (vivo, morto, etc)
    float size;                     // Tamanho/raio
    
public:
    virtual ~Entity() = default;
    
    // Métodos virtuais (implementados por subclasses)
    virtual void update(float deltaTime, Environment& env) = 0;
    virtual void die() = 0;
    virtual std::string getType() const = 0;
    virtual float getResourceConsumption() const = 0;
    
    // Getters
    EntityID getId() const;
    Vector2D getPosition() const;
    float getAge() const;
    float getEnergy() const;
    EntityState getState() const;
    float getSize() const;
    
    // Métodos comuns
    void moveTo(Vector2D newPosition);
    void setEnergy(float newEnergy);
    void addAge(float years);
    bool isAlive() const;
    float getDistance(const Entity& other) const;
};
```

### Estados Possíveis

```cpp
enum class EntityState {
    ALIVE = 0,       // Entidade viva e ativa
    DORMANT = 1,     // Entidade em dormência (hibernação)
    DYING = 2,       // Em processo de morte
    DEAD = 3,        // Entidade morta (será removida)
    RESTING = 4      // Descansando/recuperando
};
```

### Propriedades Comuns

| Propriedade | Tipo | Descrição | Intervalo |
|------------|------|-----------|-----------|
| `id` | EntityID | Identificador único | - |
| `position` | Vector2D | Coordenadas X, Y | [0, width] × [0, height] |
| `age` | float | Idade em anos-simulação | [0, maxAge] |
| `energy` | float | Energia vital | [0, maxEnergy] |
| `state` | EntityState | Estado atual | ALIVE, DORMANT, DYING, DEAD |
| `size` | float | Raio/tamanho | [0, maxSize] |

---

## 🌱 Entidade: Plant (Planta)

### Definição

A classe `Plant` representa organismos fotossintetizantes que:
- Absorvem água e nutrientes do solo
- Realizam fotossíntese
- Crescem ao longo do tempo
- Reproduzem-se
- Morrem naturalmente

### Estrutura

```cpp
class Plant : public Entity {
private:
    // Atributos de planta
    float height;                   // Altura em metros
    float rootDepth;                // Profundidade das raízes
    int age;                        // Idade em ticks
    int reproductionAge;            // Idade mínima para reprodução
    float nutritionLevel;           // Nível de nutrientes armazenados
    float waterContent;             // Quantidade de água armazenada
    PlantType type;                 // Tipo de planta (árvore, arbusto, etc)
    
    // Taxas de crescimento
    float growthRate;               // Taxa de crescimento por tick
    float photosynthesisRate;       // Taxa de fotossíntese
    
public:
    // Inicialização
    Plant(PlantType type, Vector2D position);
    
    // Métodos principais
    void update(float deltaTime, Environment& env) override;
    void photosynthesize(float sunlight);
    void absorbWaterAndNutrients(const Environment& env);
    void grow();
    void reproduce();
    void die() override;
    
    // Consultas
    bool canReproduce() const;
    float getResourceConsumption() const override;
    bool needsWater() const;
    bool needsNutrients() const;
};
```

### Tipos de Plantas

```cpp
enum class PlantType {
    GRASS = 0,          // Grama - crescimento rápido, tamanho pequeno
    SHRUB = 1,          // Arbusto - crescimento médio, tamanho médio
    TREE = 2,           // Árvore - crescimento lento, tamanho grande
    FLOWER = 3,         // Flor - ciclo curto, pouca energia
    CROP = 4            // Plantação - ciclo de crescimento controlado
};
```

### Propriedades por Tipo

| Tipo | Height (m) | Root Depth (m) | Growth Rate | Reproduction Age | Energy Max |
|------|-----------|-----------------|-------------|-----------------|------------|
| GRASS | 0.3 | 0.2 | 2.0 | 30 ticks | 50 |
| SHRUB | 2.0 | 0.8 | 1.2 | 100 ticks | 150 |
| TREE | 10.0 | 3.0 | 0.5 | 500 ticks | 500 |
| FLOWER | 1.0 | 0.3 | 1.5 | 50 ticks | 40 |
| CROP | 2.5 | 0.6 | 1.8 | 80 ticks | 120 |

### Ciclo de Vida da Planta

```
┌──────────────┐
│ Semente      │
│ (Dormência)  │
└────┬─────────┘
     │ (Recebe água + luz)
     ▼
┌──────────────┐
│ Germinação   │
│ (Crescimento)│
└────┬─────────┘
     │ (Cresce até Age = ReproductionAge)
     ▼
┌──────────────────┐
│ Maturidade       │
│ (Reprodução)     │
│ (Max Growth)     │
└────┬─────────────┘
     │
  ┌──┴────┐
  │ (com Ticks)
  │       └─────────────────────┐
  ▼                             ▼
┌────────────┐          ┌──────────────┐
│ Envelhecer │          │ Reproduzir   │
(Senescência)│          │ (Sementes)   │
└────┬───────┘          └──────┬───────┘
     │                         │
     │  (Age >= MaxAge)   (Espalha sementes)
     │                         │
     ▼                         ▼
     └────────┬────────────────┘
              │
              ▼
        ┌──────────────┐
        │ Morte        │
        │(Decomposição)│
        └──────────────┘
```

### Fórmulas de Simulação

#### Fotossíntese
```
energy_gained = photosynthesisRate × sunlight × (1 - waterLoss)
waterLoss = max(0, 1 - (waterContent / maxWater))
```

#### Absorção de Água e Nutrientes
```
water_absorbed = min(waterNeeded, availableWater × rootEfficiency)
nutrients_absorbed = min(nutrientsNeeded, availableNutrients × rootEfficiency)
rootEfficiency = rootDepth / (rootDepth + 1)
```

#### Taxa de Crescimento
```
growth_factor = (nutrition × water_current / max_water) ^ 0.5
new_height = height + (growthRate × growth_factor × deltaTime)
```

#### Reprodução
```
offspring_energy = energy × 0.3  // 30% da energia para sementes
num_seeds = floor((energy - survival_energy) / seed_energy)
survival_energy = energy_consumption × lifetime_remaining
```

---

## 👤 Entidade: Human (Ser Humano)

### Definição

A classe `Human` representa agentes inteligentes que:
- Movem-se autonomamente
- Tomam decisões baseadas em necessidades
- Constroem estruturas
- Consomem recursos
- Crescem e envelhecem
- Podem colaborar ou competir

### Estrutura

```cpp
class Human : public Entity {
private:
    // Atributos pessoais
    std::string name;               // Nome identificador
    int age;                        // Idade em ticks
    
    // Atributos físicos
    float strength;                 // Força (1-10)
    float intelligence;             // Inteligência (1-10)
    float constitution;             // Constituição/saúde (1-10)
    
    // Estados básicos
    float hunger;                   // Nível de fome (0-100)
    float thirst;                   // Nível de sede (0-100)
    float tiredness;                // Nível de cansaço (0-100)
    
    // Necessidades e comportamento
    HumanBehavior currentBehavior;  // Comportamento ativo
    HumanNeed primaryNeed;          // Necessidade primária
    std::vector<ConstructionProject> projects;
    
    // Inventário e recursos
    std::map<ResourceType, float> inventory;
    float carryCpacity;             // Capacidade de carregamento
    
    // Memória e objetivos
    std::vector<Point> exploredAreas;
    std::vector<EntityID> knownPlants;
    
public:
    Human(std::string name, Vector2D position);
    
    void update(float deltaTime, Environment& env) override;
    void makeBehaviorDecision(const Environment& env);
    void consumeResources();
    void build(const ConstructionProject& project);
    void grow();
    void die() override;
    
    // Comportamentos específicos
    void seek(ResourceType resource);
    void consume(ResourceType resource, float amount);
    void rest();
    void construct();
    
    // Consultas
    HumanNeed evaluateNeeds() const;
    float getResourceConsumption() const override;
    bool canCarry(float weight) const;
};
```

### Estados Básicos do Humano

```cpp
enum class HumanNeed {
    HUNGER = 0,         // Necessidade de comida
    THIRST = 1,         // Necessidade de água
    FATIGUE = 2,        // Necessidade de descanso
    SAFETY = 3,         // Necessidade de segurança
    BUILDING = 4        // Vontade de construir/melhorar
};

enum class HumanBehavior {
    IDLE = 0,           // Ocioso, explorando
    SEEKING_FOOD = 1,   // Procurando comida
    SEEKING_WATER = 2,  // Procurando água
    RESTING = 3,        // Descansando
    BUILDING = 4,       // Construindo estrutura
    FARMING = 5,        // Cultivando plantas
    EXPLORING = 6       // Explorando novo território
};
```

### Atributos Físicos

| Atributo | Min | Max | Impacto |
|----------|-----|-----|---------|
| Strength (Força) | 1 | 10 | Velocidade de construção, capacidade de carregamento |
| Intelligence (Inteligência) | 1 | 10 | Qualidade de decisões, eficiência de construção |
| Constitution (Constituição) | 1 | 10 | Resistência, velocidade de recuperação |

### Estados de Necessidade

| Necessidade | Min | Max | Crítico | Efeito |
|-------------|-----|-----|---------|--------|
| Hunger (Fome) | 0 | 100 | > 80 | Reduz performance, pode morrer |
| Thirst (Sede) | 0 | 100 | > 90 | Reduz performance crítica, morte rápida |
| Tiredness (Cansaço) | 0 | 100 | > 85 | Reduz ações, precisa descansar |

### Ciclo de Vida do Humano

```
┌──────────────┐
│ Nascimento   │
│ (Infância)   │
└────┬─────────┘
     │ (Age < reproductionAge)
     │ (Crescimento - 0.5x eficiência)
     ▼
┌──────────────┐
│ Puberdade    │
│ (Adolescência)│
└────┬─────────┘
     │ (Age = reproductionAge)
     │ (Eficiência aumenta gradualmente)
     ▼
┌──────────────┐
│ Adultez      │
│ (Produtivo)  │
│ (Max Eficien)│
└────┬─────────┘
     │ (Age < elderAge)
     │
  ┌──┴────┐
  │ (com Ticks)
  │       └─────────────────────┐
  ▼                             ▼
┌────────────┐          ┌──────────────┐
│ Envelhecer │          │ Reproduzir   │
│ (Terceira  │          │ (Gerar Filho)│
│  Idade)    │          │ (se condições)│
└────┬───────┘          └──────┬───────┘
     │                         │
     │ (Age >= elderAge)   (Criar novo Human)
     │ (Eficiência cai)        │
     ▼                         ▼
     └────────┬─────────────────┘
              │
              ▼
        ┌──────────────┐
        │ Morte        │
        │ (Fim de vida)│
        └──────────────┘
```

### Fórmulas de Simulação

#### Consumo de Recursos
```
daily_caloric_need = baseCalories × (1 + (strength / 10) × 0.2)
water_need_per_tick = 0.5 + (constitution / 10) × 0.1
hunger_increase_per_tick = daily_caloric_need / (24 × 60)  // minutos por tick
```

#### Eficiência de Trabalho (Construção)
```
work_efficiency = (strength / 10) × (intelligence / 10) × (1 - tiredness/100) × condition_factor
construction_progress = work_efficiency × work_rate × deltaTime
```

#### Tomada de Decisão
```
// Score para cada necessidade (0-100)
hunger_score = hunger * weight_hunger
thirst_score = thirst * weight_thirst
tiredness_score = tiredness * weight_tiredness
building_score = distance_to_project * weight_building

// Seleciona ação com maior score
behavior = select_max(hunger_score, thirst_score, tiredness_score, building_score)
```

#### Movimento e Busca
```
// Busca por recurso mais próximo conhecido
target = find_nearest_resource(seeking_type)
move_toward(target, speed)

// Se não encontrou, exploração aleatória
if (target == null) explore_randomly()
```

---

## 🔄 Interações entre Entidades

### 1. Humano-Planta: Colheita

```cpp
if (human.collidesWith(plant)) {
    if (human.currentBehavior == SEEKING_FOOD) {
        // Humano colhe energia da planta
        amount = min(human.hungerDeficit, plant.getEnergy() * 0.3);
        human.consumeFood(amount);
        plant.takeDamage(amount);
        
        if (plant.energy < min_energy) {
            plant.die();
        }
    }
}
```

### 2. Planta-Planta: Competição por Recursos

```cpp
// Plantas próximas competem por água e nutrientes
nearby_plants = environment.getNearby(plant, competition_radius);
for (other : nearby_plants) {
    // Reduz recursos disponíveis proporcionalmente
    resource_split = 1.0 / nearby_plants.count();
    other.setResourceFraction(resource_split);
}
```

### 3. Humano-Humano: Colaboração em Construção

```cpp
// Múltiplos humanos colaborando
for (project : constructionProjects) {
    humans_working = project.getWorkingHumans();
    combined_efficiency = sum(human.work_efficiency for human in humans_working);
    project.progress += combined_efficiency * deltaTime;
}
```

---

## 📊 Hierarquia de Classes

```
Entity (abstract)
│
├── Plant
│   ├── GRASS
│   ├── SHRUB
│   ├── TREE
│   ├── FLOWER
│   └── CROP
│
└── Human
    ├── Attributes: strength, intelligence, constitution
    ├── Needs: hunger, thirst, tiredness
    └── Behaviors: Seeking, Building, Exploring, Resting
```

---

## 🎯 Propriedades de Criação Padrão

### Planta Padrão (TREE)
- Height: 1.0m
- Age: 0 ticks
- Energy: 100
- State: ALIVE

### Humano Padrão
- Name: "Human_[ID]"
- Age: 18 anos
- Strength: 5-7 (aleatória)
- Intelligence: 4-8 (aleatória)
- Constitution: 5-7 (aleatória)
- Hunger: 30
- Thirst: 20
- Tiredness: 10

