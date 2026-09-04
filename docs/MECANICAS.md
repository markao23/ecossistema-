# Mecânicas de Simulação - Ecossistema

## 🎮 Visão Geral das Mecânicas

As mecânicas de simulação definem como o mundo evolui ao longo do tempo. Este documento descreve todas as regras, fórmulas e algoritmos que governam a simulação.

---

## ⏱️ Sistema de Tempo

### Estrutura Temporal

```
Real World      Simulation
1 segundo   =   10 ticks

1 tick      =   1 minuto de simulação
1 hora      =   60 ticks
1 dia       =   1.440 ticks (24 × 60)
1 ano       =   525.600 ticks (365.25 × 24 × 60)
```

### Ciclo Dia/Noite

O ambiente possui um ciclo dia/noite que afeta produção de energia:

```
Hora da Simulação   Intensidade Solar
0:00 - 6:00 (6h)    0% (Noite)
6:00 - 9:00 (3h)    Aumenta de 0% a 100% (Amanhecer)
9:00 - 15:00 (6h)   100% (Pico)
15:00 - 18:00 (3h)  Diminui de 100% a 0% (Entardecer)
18:00 - 24:00 (6h)  0% (Noite)

Fórmula:
hour = time % 24
if hour < 6:
    sunlight = 0
elif hour < 9:
    sunlight = (hour - 6) / 3 × 100%
elif hour < 15:
    sunlight = 100%
elif hour < 18:
    sunlight = (18 - hour) / 3 × 100%
else:
    sunlight = 0
```

### Estações (Opcional)

```
Estação      Dias           Temperatura   Umidade   Recursos
Primavera    ~91 dias       15°C          60%       Alto crescimento
Verão        ~92 dias       25°C          40%       Máxima produção
Outono       ~91 dias       15°C          50%       Diminui
Inverno      ~91 dias       5°C           70%       Mínimo
```

---

## 🌿 Mecânicas de Plantas

### 1. Fotossíntese

**Descrição:** Plantas convertem luz solar em energia.

**Fórmula:**
```
net_photosynthesis = base_rate × sunlight_factor × water_factor × nutrient_factor

Onde:
  base_rate = 2.0 energy/tick (para TREE)
  sunlight_factor = sunlight_intensity / 100  [0, 1]
  water_factor = min(1, water_content / optimal_water)  [0, 1]
  nutrient_factor = min(1, nutrition_level / optimal_nutrition)  [0, 1]

Limitação:
  max_energy = base_energy_capacity
  se current_energy + net_photosynthesis > max_energy:
    net_photosynthesis = max_energy - current_energy
```

**Exemplo (TREE ao meio-dia com ótimas condições):**
```
base_rate = 2.0
sunlight_factor = 1.0 (meio-dia)
water_factor = 1.0 (água suficiente)
nutrient_factor = 1.0 (nutrientes suficientes)

net_photosynthesis = 2.0 × 1.0 × 1.0 × 1.0 = 2.0 energia/tick
```

### 2. Absorção de Água e Nutrientes

**Descrição:** Plantas absorvem água e nutrientes do solo através de raízes.

**Fórmula:**
```
absorption_rate = base_rate × root_efficiency × soil_availability

root_efficiency = min(1, rootDepth / max_depth)
soil_availability = (soil_water / max_water + soil_nutrients / max_nutrients) / 2

water_absorbed_per_tick = 1.0 × root_efficiency × soil_water_pct
nutrients_absorbed_per_tick = 0.5 × root_efficiency × soil_nutrients_pct

Limite:
  water_content = min(max_water, water_content + water_absorbed)
  nutrition_level = min(max_nutrition, nutrition_level + nutrients_absorbed)
```

**Variáveis por Tipo de Planta:**

| Tipo | Base Rate (água) | Base Rate (nutrientes) | Max Water | Max Nutrition |
|------|------------------|----------------------|-----------|---------------|
| GRASS | 1.5 | 0.8 | 20 | 15 |
| SHRUB | 2.5 | 1.5 | 40 | 30 |
| TREE | 3.0 | 2.0 | 60 | 50 |
| FLOWER | 1.2 | 0.6 | 15 | 10 |
| CROP | 2.8 | 1.8 | 50 | 40 |

### 3. Consumo de Energia (Respiração)

**Descrição:** Plantas consomem parte de sua energia para manutenção.

**Fórmula:**
```
respiration_cost_per_tick = base_respiration × size_factor × temperature_factor

base_respiration = 0.3 energy/tick
size_factor = (height / max_height) × (root_depth / max_root_depth)
temperature_factor = 1 + (abs(temperature - optimal_temp) / 10) × 0.1

Atualizando energia:
  current_energy = max(0, current_energy - respiration_cost_per_tick)

Se current_energy <= 0:
  state = DEAD
```

### 4. Crescimento

**Descrição:** Plantas crescem em altura e profundidade de raízes.

**Fórmula:**
```
growth_factor = (energy_available / max_energy) × (water_content / max_water) × (nutrition_level / max_nutrition)
growth_factor = growth_factor ^ (1/3)  // Raiz cúbica para suavizar

height_increase = growth_rate_type × growth_factor × deltaTime
rootDepth_increase = growth_rate_type × growth_factor × 0.5 × deltaTime

Onde growth_rate_type:
  GRASS: 0.02 m/tick
  SHRUB: 0.01 m/tick
  TREE: 0.005 m/tick
  FLOWER: 0.015 m/tick
  CROP: 0.012 m/tick

Máximos por tipo:
  GRASS: 0.5 m
  SHRUB: 3.0 m
  TREE: 15.0 m
  FLOWER: 2.0 m
  CROP: 4.0 m
```

**Envelhecimento:**
```
age_increase_per_tick = 1
max_age_by_type:
  GRASS: 300 ticks (5 minutos)
  SHRUB: 2000 ticks
  TREE: 10000 ticks
  FLOWER: 200 ticks
  CROP: 1500 ticks

Se age >= max_age:
  state = DYING
```

### 5. Reprodução (Semeadura)

**Condições para Reprodução:**
```
pode_reproduzir = 
    age >= reproduction_age AND
    energy >= min_energy_to_reproduce AND
    nutrition_level >= min_nutrition AND
    height >= min_height

reproduction_age_by_type:
  GRASS: 50 ticks
  SHRUB: 200 ticks
  TREE: 1000 ticks
  FLOWER: 40 ticks
  CROP: 120 ticks

min_energy_to_reproduce = max_energy × 0.4
```

**Processo de Reprodução:**
```
Se pode_reproduzir:
  energy_for_seeds = energy × 0.25  // 25% da energia para sementes
  num_seeds = floor(energy_for_seeds / seed_energy_cost)
  
  seed_energy_cost = 5  // energia inicial de cada semente
  
  Para cada seed gerada:
    seed_position = randomPointNear(parent.position, spread_radius)
    new_plant = criar Plant do mesmo tipo em seed_position
    new_plant.energy = seed_energy_cost
    new_plant.age = 0
    environment.addEntity(new_plant)
  
  parent.energy -= energy_for_seeds
  
  // Limite de sementes por raio
  max_seeds = 5 + (intelligence_factor × 2)  // Para futuras plantas inteligentes
```

### 6. Morte e Decomposição

**Condições de Morte:**
```
planta.morre_se:
  energy <= 0 OR
  age >= max_age OR
  state == DYING (por 10+ ticks)
```

**Processo de Morte:**
```
quando estado muda para DEAD:
  // Libera recursos de volta ao solo
  released_water = water_content × 0.7  // 70% volta ao solo
  released_nutrients = nutrition_level × 0.8  // 80% volta ao solo
  
  soil.water += released_water
  soil.nutrients += released_nutrients
  
  // Retirar do mundo
  environment.removeEntity(id)
```

---

## 👤 Mecânicas de Humanos

### 1. Necessidades Básicas

**Fome (Hunger):**
```
fome_aumento_por_tick = daily_caloric_need / ticks_por_dia
daily_caloric_need = 2000 + (strength - 5) × 200  // kcal

Onde:
  ticks_por_dia = 1440 ticks
  fome_aumento_por_tick = daily_caloric_need / 1440

Se humano consome comida:
  energy_gained = food_calories × 0.8  // 80% de eficiência
  fome -= energy_gained
  
  Se fome < 0:
    fome = 0
    energy += max(0, energy_gained + fome)  // Armazena como energia extra
```

**Sede (Thirst):**
```
sede_aumento_por_tick = 0.15 + (constitution - 5) × 0.02

Se humano bebe água:
  thirst -= 20 por 1 unidade de água
  
Se sede > 80:
  mobility_factor = 1 - (sede - 80) / 20  // Movimento reduzido
  
Se sede > 90:
  condition_factor = 0.5  // Severamente afetado
  
Se sede >= 100:
  human.morre()  // Morte por desidratação
```

**Cansaço (Tiredness):**
```
tiredness_increase_work = 0.05 × work_intensity
tiredness_increase_movement = 0.02 × speed

Se humano está descansando:
  tiredness_decrease = 0.5 por tick
  
Se tiredness > 80:
  work_efficiency -= 50%
  
Se tiredness > 95:
  human.forced_rest()  // Desmaia/descansa
```

### 2. Eficiência de Trabalho

**Fórmula Geral:**
```
efficiency = 
    base_efficiency 
    × physical_factor 
    × mental_factor 
    × condition_factor

physical_factor = strength / 10
mental_factor = intelligence / 10
condition_factor = (1 - hunger/200) × (1 - thirst/200) × (1 - tiredness/100)

condition_factor = max(0, condition_factor)  // Não pode ser negativo

max_efficiency = 1.0 (100%)
```

**Aplicações:**

```cpp
// Construção
construction_speed = efficiency × base_construction_rate
construction_speed *= building_difficulty_modifier

// Movimento
movement_speed = efficiency × base_speed
movement_speed *= terrain_difficulty

// Colheita/Busca
search_efficiency = efficiency × base_search_rate
```

### 3. Comportamento e Tomada de Decisão

**Sistema de Scores:**
```
// Calcula score para cada possível ação
scores = {
    SEEK_FOOD: hunger * 2.0,
    SEEK_WATER: thirst * 2.5,  // Água é mais crítica
    REST: tiredness * 1.5,
    BUILD: distance_to_projects * 0.1 + construction_motivation
}

// Adiciona fatores ambientais
if (nearby_food):
    scores[SEEK_FOOD] *= 1.5  // Motiva se comida perto
    
if (no_water_found_recently):
    scores[SEEK_WATER] *= 2.0  // Urgência aumenta

// Seleciona ação com maior score
best_action = argmax(scores)
```

**Lógica de Busca:**
```
Quando buscando recurso X:
  1. Verifica proximidade (raio: 10 unidades)
  2. Se encontrou: move para lá
  3. Se não: 
     a. Consulta memória de locais conhecidos
     b. Se tem local na memória: vai lá
     c. Se não: explora aleatoriamente
     d. Registra novo recurso encontrado

Memória de Recursos (máx 20 locais por tipo):
  Se encontrou recurso:
    resource_memory.add(position, tick_encontrado)
  
  Se recurso esgotado:
    resource_memory.remove(position)
  
  Se recurso antigo (> 1000 ticks):
    priority baixa, pode ser revisitado
```

### 4. Movimento e Navegação

**Velocidade de Movimento:**
```
base_speed = 2.0 unidades/tick
actual_speed = base_speed × efficiency × terrain_factor

Onde:
  efficiency = conforme seção 2 acima
  terrain_factor = 1.0 (normal) a 0.5 (difícil)

Quando se movendo para alvo:
  direction = normalize(target - current_position)
  new_position = current_position + direction × actual_speed
```

**Busca de Caminho (A* simplificado):**
```
Se caminho bloqueado:
  1. Tentar contornar obstáculo
  2. Se não conseguir: procurar rota alternativa
  3. Se rota não encontrada: explorar aleatoriamente
```

### 5. Construção e Projetos

**Tipos de Construção:**
```cpp
enum ConstructionType {
    SHELTER,        // Abrigo - proteção
    STORAGE,        // Armazenamento - recursos
    FARM,          // Fazenda - produção de comida
    WELL,          // Poço - acesso a água
    WALL           // Muro - defesa/controle
};
```

**Custo de Construção:**
```
Para cada projeto:
  total_work_required = base_work × difficulty_modifier
  
Base por tipo:
  SHELTER: 1000 unidades de trabalho
  STORAGE: 800 unidades
  FARM: 600 unidades
  WELL: 400 unidades
  WALL: 500 unidades

difficulty_modifier:
  Fácil: 0.8
  Normal: 1.0
  Difícil: 1.5

// Progresso da construção
construction_progress += worker_efficiency × work_rate × deltaTime

work_rate = 10  // unidades de trabalho por efficiency-tick

Se construction_progress >= total_work_required:
  projeto.completo = true
  projeto.remover()
  estrutura.criar()  // Cria estrutura no mundo
```

**Benefícios da Construção:**
```
SHELTER:
  - Aumenta resistência a condições climáticas
  - Melhora qualidade de sono (recuperação de tiredness)
  
STORAGE:
  - Aumenta capacidade de carregar recursos
  - Permite armazenamento centralizado
  
FARM:
  - Acelera crescimento de plantas próximas
  - Produz comida regularmente
  
WELL:
  - Fornece água limpa
  - Reduz necessidade de buscar água
  
WALL:
  - Define território
  - Oferece proteção
```

### 6. Reprodução e Crescimento

**Ciclo de Vida do Humano:**
```
Fase               Age Range      Efficiency   Duração (ticks)
Infância (Child)   0 - 5 anos     50%          2190
Adolescência       5 - 13 anos    75%          2920
Adultez            13 - 60 anos   100%         17055
Terceira Idade     60 - 80 anos   60%          7300
Fim da Vida        80+ anos       30%          ...

Conversão:
  1 ano = 525.600 ticks
  age_increase_per_tick = 1/525600 anos
```

**Reprodução:**
```
pode_reproduzir = 
    age >= 13 anos AND
    age <= 50 anos AND
    energy >= 100 AND
    hunger < 30 AND
    thirst < 30

Se pode e condições favoráveis:
  offspring_energy_cost = 150
  criança_energy_inicial = 75
  
  parent.energy -= offspring_energy_cost
  
  new_human = criar Human
  new_human.age = 0
  new_human.energy = criança_energy_inicial
  new_human.position = parent.position + randomOffset(5)
  
  environment.addEntity(new_human)
```

### 7. Morte

**Condições de Morte:**
```
humano.morre_se:
  energy <= 0 OR
  thirst >= 100 OR
  age >= max_lifespan (100 anos) OR
  hunger >= 100 (após estar sem comida por muito tempo)

max_lifespan = 36500 ticks (100 anos)
```

---

## 🌍 Mecânicas Ambientais

### 1. Regeneração de Recursos Globais

**Água:**
```
global_water_per_tick = base_regeneration × season_factor × rain_factor

base_regeneration = 5.0 unidades/tick

Fatores sazonais:
  Primavera: 1.5x
  Verão: 0.8x
  Outono: 1.2x
  Inverno: 1.8x (chuvas, neve)

Consumo por entidade:
  Se planta ou humano bem distribuído, reduz global proporcional

global_water = min(max_water, global_water + net_water_change)
max_water = 10000 unidades
```

**Nutrientes do Solo:**
```
global_nutrients_per_tick = base_regeneration × decomposition_factor

base_regeneration = 2.0 unidades/tick
decomposition_factor = (dead_matter / max_dead_matter) × 0.5 + 0.5

global_nutrients = min(max_nutrients, global_nutrients + global_nutrients_per_tick)
max_nutrients = 8000 unidades

Morte de entidades contribui:
  plant.morre():
    dead_matter += plant.biomass
  
  dead_matter_decay_per_tick = dead_matter × 0.001
  global_nutrients += dead_matter_decay_per_tick × nutrient_yield
  dead_matter -= dead_matter_decay_per_tick
```

### 2. Temperatura e Clima

**Variação de Temperatura:**
```
base_temp = 20°C
seasonal_variation:
  Primavera: 15°C
  Verão: 25°C
  Outono: 15°C
  Inverno: 5°C

daily_variation = amplitude × sin((hora - 6) × π / 12)
amplitude = 5°C (máximo)

current_temp = base_temp + seasonal_effect + daily_variation

Efeitos:
  temp < 0°C:    plantas crescem 50% mais lento, humanos perdem 2x energia
  0°C - 10°C:    crescimento normal plantas, humanos -25% eficiência
  10°C - 30°C:   ótimo para todas entidades
  30°C - 40°C:   plantas ficam lentas, humanos -10% eficiência
  temp > 40°C:   plantas morrem, humanos perdem 5x energia
```

---

## 📊 Resumo de Fórmulas Críticas

| Processo | Fórmula | Intervalo |
|----------|---------|-----------|
| Fotossíntese | base × sunlight × water × nutrient | +0 a +10 energy |
| Respiration | 0.3 × size × temperature | -0.5 a -1.5 energy |
| Crescimento | rate × (energy/max)^(1/3) | +0.001 a +0.02 m/tick |
| Reprodução | energy × 0.25 / seed_cost | 1-20 seeds |
| Fome | need / ticks_por_dia | +0.05 a +0.2 hunger/tick |
| Eficiência | (strength/10) × (intel/10) × conditions | 0.0 a 1.0 |
| Construção | efficiency × 10 × deltaTime | +0 a +100 progress/tick |

