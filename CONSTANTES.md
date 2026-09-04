# Simulação de Ecossistema - Constantes e Configuração

## Constantes de Configuração do Mundo

### Dimensões
- **Largura do Mundo:** 1024 unidades
- **Altura do Mundo:** 768 unidades
- **Célula Grid:** 1x1 unidade

### Sistema de Tempo
- **Ticks por Segundo:** 10
- **Ticks por Minuto:** 600
- **Ticks por Hora:** 36,000
- **Ticks por Dia:** 1,440 (24 × 60)
- **Ticks por Ano:** 525,600 (365.25 × 24 × 60)

### Recursos Globais - Limites
- **Água Máxima:** 10,000 unidades
- **Nutrientes Máximos:** 8,000 unidades
- **Regeneração de Água Base:** 5.0 unidades/tick
- **Regeneração de Nutrientes Base:** 2.0 unidades/tick

### Plantas - GRASS
- **Altura Máxima:** 0.5 m
- **Profundidade de Raízes:** 0.2 m
- **Taxa de Fotossíntese:** 2.0 energy/tick
- **Taxa de Respiração:** 0.15 energy/tick
- **Taxa de Crescimento:** 0.02 m/tick
- **Idade de Reprodução:** 50 ticks (~0.83 minuto)
- **Idade Máxima:** 300 ticks (~5 minutos)
- **Energia Máxima:** 50
- **Sementes por Reprodução:** 3-8
- **Raio de Dispersão:** 3-5 unidades

### Plantas - SHRUB
- **Altura Máxima:** 3.0 m
- **Profundidade de Raízes:** 0.8 m
- **Taxa de Fotossíntese:** 1.5 energy/tick
- **Taxa de Respiração:** 0.25 energy/tick
- **Taxa de Crescimento:** 0.01 m/tick
- **Idade de Reprodução:** 200 ticks (~3.3 minutos)
- **Idade Máxima:** 2,000 ticks (~33 minutos)
- **Energia Máxima:** 150
- **Sementes por Reprodução:** 2-5
- **Raio de Dispersão:** 5-8 unidades

### Plantas - TREE
- **Altura Máxima:** 15.0 m
- **Profundidade de Raízes:** 3.0 m
- **Taxa de Fotossíntese:** 2.0 energy/tick
- **Taxa de Respiração:** 0.3 energy/tick
- **Taxa de Crescimento:** 0.005 m/tick
- **Idade de Reprodução:** 1,000 ticks (~16.7 minutos)
- **Idade Máxima:** 10,000 ticks (~166.7 minutos)
- **Energia Máxima:** 500
- **Sementes por Reprodução:** 1-3
- **Raio de Dispersão:** 10-20 unidades

### Plantas - FLOWER
- **Altura Máxima:** 2.0 m
- **Profundidade de Raízes:** 0.3 m
- **Taxa de Fotossíntese:** 1.8 energy/tick
- **Taxa de Respiração:** 0.20 energy/tick
- **Taxa de Crescimento:** 0.015 m/tick
- **Idade de Reprodução:** 40 ticks (~0.67 minuto)
- **Idade Máxima:** 200 ticks (~3.3 minutos)
- **Energia Máxima:** 40
- **Sementes por Reprodução:** 5-15
- **Raio de Dispersão:** 4-10 unidades

### Plantas - CROP
- **Altura Máxima:** 4.0 m
- **Profundidade de Raízes:** 0.6 m
- **Taxa de Fotossíntese:** 1.9 energy/tick
- **Taxa de Respiração:** 0.28 energy/tick
- **Taxa de Crescimento:** 0.012 m/tick
- **Idade de Reprodução:** 120 ticks (~2 minutos)
- **Idade Máxima:** 1,500 ticks (~25 minutos)
- **Energia Máxima:** 120
- **Sementes por Reprodução:** 4-10
- **Raio de Dispersão:** 3-6 unidades

### Humanos - Atributos Físicos
- **Força Range:** 1-10 (média 5-7)
- **Inteligência Range:** 1-10 (média 4-8)
- **Constituição Range:** 1-10 (média 5-7)

### Humanos - Necessidades Básicas
- **Fome - Máxima:** 100
- **Fome - Crítica:** > 80
- **Fome - Letal:** >= 100

- **Sede - Máxima:** 100
- **Sede - Crítica:** > 90
- **Sede - Letal:** >= 100

- **Cansaço - Máxima:** 100
- **Cansaço - Crítico:** > 85

### Humanos - Consumo de Recursos
- **Calorias Diárias Base:** 2,000 kcal
- **Variação por Força:** ±200 kcal por ponto
- **Necessidade de Água:** 2.0-2.5 unidades/dia
- **Taxa de Fome Aumento:** 0.05-0.1/tick (depende de força)
- **Taxa de Sede Aumento:** 0.15 + (constituição/10) × 0.02/tick

### Humanos - Movimento
- **Velocidade Base:** 2.0 unidades/tick
- **Modificador de Eficiência:** ±100% (basado em eficiência)
- **Modificador de Terreno:** 0.5x-1.0x
- **Raio de Percepção:** 15-20 unidades

### Humanos - Ciclo de Vida
- **Idade de Reprodução:** 13 anos (6,832,800 ticks)
- **Idade Máxima de Reprodução:** 50 anos
- **Idade Máxima de Vida:** 100 anos (52,560,000 ticks)
- **Energia Máxima:** 1,000

### Humanos - Construção
- **SHELTER - Trabalho Necessário:** 1,000 unidades
- **STORAGE - Trabalho Necessário:** 800 unidades
- **FARM - Trabalho Necessário:** 600 unidades
- **WELL - Trabalho Necessário:** 400 unidades
- **WALL - Trabalho Necessário:** 500 unidades

- **Taxa de Trabalho Base:** 10 unidades/efficiency-tick
- **Modificador de Dificuldade:** 0.8x (Fácil) a 1.5x (Difícil)

### Ambiente - Temperatura
- **Temperatura Base:** 20°C
- **Temperatura Ótima:** 20°C
- **Variação Sazonal:**
  - Primavera: 15°C
  - Verão: 25°C
  - Outono: 15°C
  - Inverno: 5°C
- **Variação Diária:** ±5°C

### Ambiente - Ciclo Dia/Noite
- **Horário de Amanhecer:** 6:00-9:00 (3 horas)
- **Horário de Pico:** 9:00-15:00 (6 horas, 100% luz)
- **Horário de Entardecer:** 15:00-18:00 (3 horas)
- **Horário de Noite:** 18:00-6:00 (12 horas, 0% luz)

### Estações
- **Primavera:** ~91 dias, +50% crescimento plantas
- **Verão:** ~92 dias, máxima produção
- **Outono:** ~91 dias, -20% crescimento
- **Inverno:** ~91 dias, -50% crescimento, +regeneração água

### Performance - Limites
- **Máximo de Entidades:** 10,000
- **Máximo de Projetos de Construção:** 1,000
- **Máximo de Células Atualizadas/Tick:** 2,000
- **Máximo de Cálculos Físicos/Tick:** 500

---

## Configuração Recomendada para Simulação

### Scenario "Fácil"
```
initialPlants = 300
initialHumans = 5
resourceScarcity = 0.8x (abundante)
simulationSpeed = 1.0x
```

### Scenario "Normal"
```
initialPlants = 500
initialHumans = 10
resourceScarcity = 1.0x
simulationSpeed = 1.0x
```

### Scenario "Desafiador"
```
initialPlants = 200
initialHumans = 15
resourceScarcity = 1.5x (escasso)
simulationSpeed = 1.0x
```

### Scenario "Sandbox"
```
initialPlants = 1000
initialHumans = 50
resourceScarcity = 0.5x (super abundante)
simulationSpeed = 2.0x (mais rápido)
```

---

## Notas Importantes

1. **Tick = 1 minuto de simulação real**
   - Facilita testes e prototipagem
   - 1 hora = 60 ticks (60 minutos)
   - 1 dia = 1.440 ticks

2. **Fórmulas são não-lineares**
   - Crescimento depende de múltiplos fatores
   - Eficiência é multiplicativa, não aditiva
   - Recursos têm limites globais

3. **Balanceamento**
   - Plantas devem dar mais energia que humanos consomem
   - Ciclos reprodutivos são críticos para sobrevivência
   - Morte natural mantém população sob controle

4. **Escalabilidade**
   - Sistema foi desenhado para suportar 1000+ entidades
   - Grid-based para otimizações espaciais
   - Atualização lazy de propriedades ambientais

