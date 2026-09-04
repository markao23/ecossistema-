# Especificações Técnicas - Simulação de Ecossistema

## 📋 Visão Geral

Este documento detalha as especificações técnicas da implementação, incluindo APIs, estruturas de dados, formatos e configurações.

---

## 🔧 Configuração do Projeto

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)
project(Ecosystem VERSION 1.0.0 LANGUAGES CXX)

# Standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

# Diretórios de inclusão
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Fonte
file(GLOB_RECURSE SOURCES "src/**/*.cpp")
file(GLOB_RECURSE HEADERS "src/**/*.h")

# Executável principal
add_executable(ecosystem ${SOURCES})

# Testes (opcional)
enable_testing()
add_subdirectory(tests)
```

---

## 📦 Estruturas de Dados Principais

### 1. Vector2D

**Localização:** `src/utils/Vector2D.h`

```cpp
struct Vector2D {
    float x, y;
    
    // Construtores
    Vector2D();
    Vector2D(float x, float y);
    
    // Operações aritméticas
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;
    
    // Operações vetoriais
    float dot(const Vector2D& other) const;
    float cross(const Vector2D& other) const;
    float magnitude() const;
    Vector2D normalized() const;
    float distance(const Vector2D& other) const;
    
    // Comparação
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;
};
```

### 2. EntityID

**Tipo:** `typedef uint64_t EntityID`

Identificador único para cada entidade. Gerado sequencialmente ou com UUID.

```cpp
class EntityIDGenerator {
private:
    static uint64_t nextID;
    
public:
    static EntityID generate();
    static void reset();
};
```

### 3. Cell (Célula do Grid)

**Localização:** `src/core/Cell.h`

```cpp
struct Cell {
    // Posição
    int x, y;
    
    // Recursos
    float water;           // 0-100
    float nutrients;       // 0-100
    
    // Propriedades
    int terrainType;       // 0: normal, 1: montanhoso, etc
    float altitude;        // -100 a 100 metros
    
    // Ocupação
    EntityID primaryOccupant;     // ID de planta ou construção
    std::vector<EntityID> secondary;  // IDs de humanos presentes
    
    // Métodos
    bool isWalkable() const;
    bool hasPlant() const;
    float getResourceDensity() const;
};
```

### 4. ConstructionProject

**Localização:** `src/systems/BuildingSystem.h`

```cpp
struct ConstructionProject {
    ProjectID id;
    ConstructionType type;
    Vector2D position;
    
    // Progresso
    float progress;         // 0-100%
    float totalWorkRequired;
    
    // Recursos necessários
    std::map<ResourceType, float> resourceRequirements;
    std::map<ResourceType, float> resourcesGathered;
    
    // Humanos trabalhando
    std::vector<EntityID> workingHumans;
    
    // Estado
    bool isComplete() const;
    float getCompletion() const;
    bool hasResourcesAvailable() const;
};
```

---

## 🎯 APIs Principais

### Environment API

```cpp
class Environment {
public:
    // Inicialização
    void initialize(int width, int height);
    void shutdown();
    
    // Gestão de entidades
    void addEntity(std::unique_ptr<Entity> entity);
    void removeEntity(EntityID id);
    Entity* getEntity(EntityID id);
    std::vector<Entity*> getAllEntities();
    std::vector<Entity*> getEntitiesInRadius(Vector2D center, float radius);
    std::vector<Entity*> getEntitiesOfType(EntityType type);
    
    // Acesso ao mapa
    Cell& getCell(int x, int y);
    Cell& getCell(Vector2D pos);
    bool isValidPosition(Vector2D pos) const;
    bool isCellWalkable(Vector2D pos) const;
    
    // Gestão de recursos
    void addWater(float amount);
    void removeWater(float amount);
    void addNutrients(float amount);
    void removeNutrients(float amount);
    float getWaterLevel() const;
    float getNutrientLevel() const;
    
    // Propriedades ambientais
    float getTemperature() const;
    float getHumidity() const;
    float getSunlight() const;
    int getTimeOfDay() const;  // 0-23
    int getDayCount() const;
    Season getCurrentSeason() const;
    
    // Atualização
    void update(float deltaTime);
    void updateEnvironmentalConditions(float deltaTime);
    void updateDayNightCycle(float deltaTime);
};
```

### SimulationEngine API

```cpp
class SimulationEngine {
public:
    // Singleton
    static SimulationEngine* getInstance();
    
    // Controle
    void initialize(SimulationConfig config);
    void update();
    void pause();
    void resume();
    void stop();
    bool isRunning() const;
    
    // Acesso
    Environment& getEnvironment();
    int getCurrentTick() const;
    float getSimulationSpeed() const;
    void setSimulationSpeed(float speed);
    
    // Observadores
    void subscribe(SimulationObserver* observer);
    void unsubscribe(SimulationObserver* observer);
    
    // Consultas
    SimulationStats getStatistics() const;
};
```

### Entity API

```cpp
class Entity {
protected:
    EntityID id;
    Vector2D position;
    float age;
    float energy;
    EntityState state;
    float size;
    
public:
    virtual ~Entity() = default;
    
    // Métodos virtuais
    virtual void update(float deltaTime, Environment& env) = 0;
    virtual void die() = 0;
    virtual std::string getType() const = 0;
    virtual float getResourceConsumption() const = 0;
    
    // Accessores
    EntityID getId() const { return id; }
    Vector2D getPosition() const { return position; }
    float getAge() const { return age; }
    float getEnergy() const { return energy; }
    EntityState getState() const { return state; }
    float getSize() const { return size; }
    bool isAlive() const { return state == EntityState::ALIVE; }
    
    // Mutadores
    void setPosition(Vector2D newPos) { position = newPos; }
    void setEnergy(float newEnergy) { energy = std::clamp(newEnergy, 0.0f, getMaxEnergy()); }
    void setAge(float newAge) { age = newAge; }
    void setState(EntityState newState) { state = newState; }
    
    // Operações
    void moveBy(Vector2D delta) { position = position + delta; }
    void moveTo(Vector2D target) { position = target; }
    float getDistanceTo(const Entity& other) const;
    
    // Cálculos
    virtual float getMaxEnergy() const = 0;
    virtual float getMaxAge() const = 0;
};
```

### Plant API

```cpp
class Plant : public Entity {
private:
    PlantType type;
    float height;
    float rootDepth;
    int ageInTicks;
    float nutritionLevel;
    float waterContent;
    
public:
    Plant(PlantType type, Vector2D position);
    
    // Ciclo de vida
    void update(float deltaTime, Environment& env) override;
    void photosynthesize(float sunlight);
    void absorbWaterAndNutrients(Environment& env);
    void grow();
    void reproduce();
    void die() override;
    
    // Consultas
    PlantType getPlantType() const { return type; }
    float getHeight() const { return height; }
    float getRootDepth() const { return rootDepth; }
    float getNutritionLevel() const { return nutritionLevel; }
    float getWaterContent() const { return waterContent; }
    bool canReproduce() const;
    bool needsWater() const;
    bool needsNutrients() const;
    
    // Modificadores
    void takeDamage(float amount);
    void addWater(float amount);
    void addNutrition(float amount);
};
```

### Human API

```cpp
class Human : public Entity {
private:
    std::string name;
    float intelligence;
    float strength;
    float constitution;
    float hunger;
    float thirst;
    float tiredness;
    HumanBehavior behavior;
    HumanNeed primaryNeed;
    std::vector<ConstructionProject*> projects;
    std::map<ResourceType, float> inventory;
    
public:
    Human(std::string name, Vector2D position);
    
    // Ciclo de vida
    void update(float deltaTime, Environment& env) override;
    void die() override;
    
    // Necessidades
    void evaluateNeeds(const Environment& env);
    void makeBehaviorDecision(const Environment& env);
    HumanNeed getPrimaryNeed() const { return primaryNeed; }
    HumanBehavior getCurrentBehavior() const { return behavior; }
    
    // Consumo
    void consumeFood(float calories);
    void consumeWater(float amount);
    void rest(float amount);
    void consumeResources(float deltaTime);
    
    // Construção
    void addProject(ConstructionProject* project);
    void removeProject(ProjectID id);
    void buildOnProject(ConstructionProject* project, float deltaTime);
    
    // Movimento
    void moveTo(Vector2D target, float speed);
    void seekResource(ResourceType type, const Environment& env);
    
    // Atributos
    float getStrength() const { return strength; }
    float getIntelligence() const { return intelligence; }
    float getConstitution() const { return constitution; }
    float getHunger() const { return hunger; }
    float getThirst() const { return thirst; }
    float getTiredness() const { return tiredness; }
    float getWorkEfficiency() const;
    
    // Utilitários
    bool canCarry(float weight) const;
    float getRemainingCapacity() const;
};
```

---

## 🏗️ Sistemas API

### PhysicsSystem

```cpp
class PhysicsSystem : public System {
public:
    void update(Environment& env, float deltaTime) override;
    
    // Colisões
    bool checkCollision(Entity& a, Entity& b);
    std::vector<Entity*> getCollidingEntities(Entity& entity, const Environment& env);
    
    // Movimento
    Vector2D calculateMovement(Entity& entity, float speed, Vector2D direction);
    bool canMoveTo(Vector2D pos, const Environment& env);
    
    // Consultas
    bool isNear(Vector2D a, Vector2D b, float radius);
    float getDistance(Vector2D a, Vector2D b);
};
```

### ResourceSystem

```cpp
class ResourceSystem : public System {
public:
    void update(Environment& env, float deltaTime) override;
    
    // Regeneração
    void regenerateResources(Environment& env, float deltaTime);
    void distributeResources(Environment& env);
    
    // Consultas
    float getWaterAvailability(Vector2D pos) const;
    float getNutrientAvailability(Vector2D pos) const;
    Vector2D findNearestResource(Vector2D pos, ResourceType type, const Environment& env);
};
```

### GrowthSystem

```cpp
class GrowthSystem : public System {
public:
    void update(Environment& env, float deltaTime) override;
    
    // Envelhecimento
    void updateAge(Entity& entity, float deltaTime);
    
    // Crescimento
    void updateGrowth(Plant& plant, float deltaTime, const Environment& env);
    
    // Reprodução
    void checkReproduction(Entity& entity, Environment& env);
    
    // Morte
    void checkDeath(Entity& entity, Environment& env);
};
```

### BuildingSystem

```cpp
class BuildingSystem : public System {
public:
    void update(Environment& env, float deltaTime) override;
    
    // Gerenciamento de projetos
    void addProject(ConstructionProject* project);
    void removeProject(ProjectID id);
    ConstructionProject* getProject(ProjectID id);
    std::vector<ConstructionProject*> getAllProjects();
    
    // Progresso
    void updateConstruction(Environment& env, float deltaTime);
    void completeProject(ConstructionProject* project, Environment& env);
    
    // Validação
    bool validateConstruction(ConstructionProject* project, const Environment& env);
};
```

---

## 📊 Enumerações e Constantes

### Tipos de Plantas

```cpp
enum class PlantType : uint8_t {
    GRASS = 0,
    SHRUB = 1,
    TREE = 2,
    FLOWER = 3,
    CROP = 4
};
```

### Estados de Entidade

```cpp
enum class EntityState : uint8_t {
    ALIVE = 0,
    DORMANT = 1,
    DYING = 2,
    DEAD = 3,
    RESTING = 4
};
```

### Comportamentos Humanos

```cpp
enum class HumanBehavior : uint8_t {
    IDLE = 0,
    SEEKING_FOOD = 1,
    SEEKING_WATER = 2,
    RESTING = 3,
    BUILDING = 4,
    FARMING = 5,
    EXPLORING = 6
};
```

### Necessidades Humanas

```cpp
enum class HumanNeed : uint8_t {
    HUNGER = 0,
    THIRST = 1,
    FATIGUE = 2,
    SAFETY = 3,
    BUILDING = 4
};
```

### Tipos de Recursos

```cpp
enum class ResourceType : uint8_t {
    WATER = 0,
    NUTRIENTS = 1,
    FOOD = 2,
    WOOD = 3,
    STONE = 4
};
```

### Estações

```cpp
enum class Season : uint8_t {
    SPRING = 0,
    SUMMER = 1,
    AUTUMN = 2,
    WINTER = 3
};
```

---

## ⚙️ Constantes de Configuração

**Localização:** `src/utils/Constants.h`

```cpp
namespace Constants {
    // Dimensões do mundo
    constexpr int WORLD_WIDTH = 1024;
    constexpr int WORLD_HEIGHT = 768;
    
    // Tempo
    constexpr float TICKS_PER_SECOND = 10.0f;
    constexpr int TICKS_PER_DAY = 1440;
    constexpr int TICKS_PER_YEAR = 525600;
    
    // Recursos
    constexpr float MAX_GLOBAL_WATER = 10000.0f;
    constexpr float MAX_GLOBAL_NUTRIENTS = 8000.0f;
    constexpr float WATER_REGEN_BASE = 5.0f;
    constexpr float NUTRIENT_REGEN_BASE = 2.0f;
    
    // Plantas - TREE
    constexpr float TREE_PHOTOSYNTHESIS_RATE = 2.0f;
    constexpr float TREE_RESPIRATION_COST = 0.3f;
    constexpr float TREE_GROWTH_RATE = 0.005f;
    constexpr float TREE_MAX_HEIGHT = 15.0f;
    constexpr int TREE_REPRODUCTION_AGE = 1000;
    constexpr int TREE_MAX_AGE = 10000;
    constexpr float TREE_MAX_ENERGY = 500.0f;
    
    // Humanos
    constexpr float HUMAN_BASE_SPEED = 2.0f;
    constexpr float HUMAN_BASE_CALORIES = 2000.0f;
    constexpr float HUMAN_BASE_WATER_NEED = 2.0f;
    constexpr int HUMAN_REPRODUCTION_AGE = 13 * TICKS_PER_YEAR;
    constexpr int HUMAN_MAX_AGE = 80 * TICKS_PER_YEAR;
    constexpr float HUMAN_MAX_ENERGY = 1000.0f;
    
    // Ambiente
    constexpr float BASE_TEMPERATURE = 20.0f;
    constexpr float OPTIMAL_TEMPERATURE = 20.0f;
    
    // Visualização (opcional)
    constexpr int WINDOW_WIDTH = 1600;
    constexpr int WINDOW_HEIGHT = 900;
}
```

---

## 📋 Configuração de Simulação

```cpp
struct SimulationConfig {
    // Mundo
    int worldWidth = 1024;
    int worldHeight = 768;
    
    // Tempo
    float simulationSpeed = 1.0f;  // 1x velocidade normal
    
    // População inicial
    int initialPlants = 500;
    int initialHumans = 10;
    
    // Dificuldade
    float resourceScarcity = 1.0f;  // 1.0 = normal
    float predatorAggressiveness = 0.5f;
    
    // Logging
    bool enableLogging = true;
    int logFrequency = 60;  // ticks entre logs
};
```

---

## 💾 Formatos de Dados

### Salvar Simulação

```json
{
  "version": "1.0.0",
  "timestamp": "2026-09-04T12:00:00Z",
  "simTick": 150000,
  "environment": {
    "width": 1024,
    "height": 768,
    "globalWater": 8500.0,
    "globalNutrients": 6200.0,
    "temperature": 22.5,
    "timeOfDay": 14
  },
  "entities": [
    {
      "id": 1,
      "type": "Plant",
      "plantType": "TREE",
      "position": { "x": 512, "y": 384 },
      "age": 5000,
      "energy": 350.5,
      "height": 8.2,
      "state": "ALIVE"
    }
  ],
  "constructionProjects": []
}
```

### Estatísticas de Simulação

```cpp
struct SimulationStats {
    int totalTicks;
    int totalPlants;
    int totalHumans;
    float averagePlantEnergy;
    float averageHumanEnergy;
    int plantsReproduced;
    int humansReproduced;
    int plantsDeadNaturally;
    int humansDeadNaturally;
    float globalWaterLevel;
    float globalNutrientLevel;
};
```

