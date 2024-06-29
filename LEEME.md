[![License][license-shield]][license-url] [![Issues][issues-shield]][issues-url]
[![Forks][forks-shield]][forks-url] [![Stars][stars-shield]][stars-url]
[![Pull Requests][pull-requests-shield]][pull-requests-url]
![Version][version-shield] ![Platform][platform-shield]
[![Code Style][code-style-shield]][code-style-url]
[![Documentation][documentation-shield]][documentation-url]
[![Build With][build-with-shield]][CMake-url]

[![Download][download-game-examples-shield]][download-game-examples-url]
<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img style="width: 10em; left: 50%;" src="doc/images/GLESC_logo_white_background.png" alt="Logo"  >
  </a>

<h3 align="center">GLESC Game Engine</h3>

  <p style="text-align: center;">
    Un motor de juego en C++ utilizando OpenGL y SDL2 basado en la arquitectura ECS.
    <br />
    <br />
        <a href="https://valydumitru01.github.io/GLESC/doc/doxy/generated-doxy/html/index.html">
            <strong>Lee la documentación de Doxygen »</strong>
        </a>
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template">Ver Demo</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues/new?labels=bug&template=bug-report```.md">
Reportar un error
</a>
    ·
    <a 
href="https://github.com/othneildrew/Best-README-Template/issues/new?labels=enhancement&template=feature-request```.md">
Solicitar una mejora</a>
  </p>
</div>

**Tabla de Contenidos**
<!-- TOC -->
  * [Acerca del Proyecto](#acerca-del-proyecto)
    * [Construido Con](#construido-con)
  * [Comenzando](#comenzando)
    * [Requisitos Previos](#requisitos-previos)
    * [Instalación](#instalación)
      * [Instalación con CLion](#instalación-con-clion)
  * [Uso](#uso)
    * [Creando un nuevo juego (o escena)](#creando-un-nuevo-juego-o-escena)
      * [Creando una entidad](#creando-una-entidad)
      * [Componentes](#componentes)
        * [TransformComponent](#transformcomponent)
        * [CollisionComponent](#collisioncomponent)
        * [PhysicsComponent](#physicscomponent)
        * [RenderComponent](#rendercomponent)
          * [Mesh](#mesh)
          * [Materiales](#materiales)
        * [InputComponent](#inputcomponent)
        * [LightComponent](#lightcomponent)
        * [SunComponent](#suncomponent)
        * [CameraComponent](#cameracomponent)
        * [FogComponent](#fogcomponent)
      * [Sistemas](#sistemas)
      * [HUD](#hud)
      * [Depuración](#depuración)
      * [Sonidos](#sonidos)
  * [Hoja de Ruta](#hoja-de-ruta)
  * [Contribuciones](#contribuciones)
  * [Licencia](#licencia)
  * [Contacto](#contacto)
  * [Reconocimientos](#reconocimientos)
<!-- TOC -->



<!-- ABOUT THE PROJECT -->

## Acerca del Proyecto

[![GLESC_game_gif.gif](doc/gifs/GLESC_game_gif.gif)][GLESC_yt_video_url]
> ⬆️⬆️⬆️ Haz clic en el gif para ver la presentación completa del motor ⬆️⬆️⬆️

GLESC es un motor de juego implementado en C++ utilizando OpenGL y SDL2. Es un proyecto final de grado para el
Grado en Ingeniería Informática en la Universidad de Oviedo. Su desarrollo duró un año y medio de trabajo a tiempo
completo de una sola persona - <a href="#contact">yo</a>. <br>
El motor permite renderizado 3D, shaders, física, colisiones, entradas y audio, aprovechando la arquitectura ECS
(buena caché).

El proyecto se desarrolló con algunos principios en mente:

* **Modularidad o Separación de Preocupaciones (SoC)**: El motor está dividido en módulos, cada uno con un propósito
  específico. Esto permite un fácil mantenimiento y escalabilidad.
* **Rendimiento**: El motor está diseñado para ser lo más rápido posible. Utiliza la arquitectura ECS, que es amigable
  con la caché.
* **DRY**: El motor está diseñado para ser lo más DRY posible, aunque a veces hay repetición de código y no es tan DRY
  como debería ser. Esto se debe a la falta de tiempo y experiencia del desarrollador. Y a veces por razones de
  legibilidad.
* **KISS**: El motor está diseñado para ser lo más simple posible. Esto no significa que sea simple. Significa que no es
  más complejo de lo necesario. Desafortunadamente, por definición, un motor de juego es una pieza de software compleja.
* **SOLID**: El motor está diseñado para ser lo más SOLID posible. Esto significa que el código es fácil de mantener y
  extender. Aprovecha la POO y el polimorfismo de C++ para mejorar los principios SOLID.
* **Documentación**: El motor está bien documentado, ya que es un requisito para la asignación del proyecto de grado.

> **Nota**: Es importante tener en cuenta las grandes limitaciones del proyecto:
> * La falta de experiencia del desarrollador
> * La falta de tiempo y las restricciones de tiempo
> * La falta de recursos (hardware y software)
> * La falta de conocimiento del desarrollador (por lo tanto, se dedicó mucho tiempo a aprender).
>
> Este proyecto no es perfecto y tiene algunos trucos feos, algunas decisiones de diseño pobres, algunos errores y
> algunos problemas de rendimiento. Pero también tiene algunas grandes decisiones de diseño, algún gran código y un gran
> rendimiento que tomó mucho tiempo y esfuerzo lograr.
>
> _No debe tomarse como referencia para un motor de juego, sino como una experiencia de aprendizaje_.

### Construido Con

<!-- Built with shields -->

- [![C++][c++-shield]][c++-url]
- [![CMake][CMake-shield]][CMake-url]
- [![OpenGL][OpenGL-shield]][OpenGL-url]
- [![SDL2][SDL2-shield]][SDL2-url]
- [![GLEW][GLEW-shield]][GLEW-url]
- [![ImGui][ImGui-shield]][ImGui-url]
- [![Mingw][Mingw-shield]][Mingw-url]
- [![Boost][Boost-shield]][Boost-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Comenzando

Las siguientes instrucciones te ayudarán a obtener una copia del proyecto y ejecutarlo en tu máquina local para
desarrollo y pruebas.

### Requisitos Previos

Aquí hay una lista de cosas que necesitas para usar el software y cómo instalarlas.

- #### Boost
  Boost es un conjunto de bibliotecas para el lenguaje de programación C++ que proporciona soporte para tareas y
  estructuras como álgebra lineal, generación de números pseudoaleatorios, multithreading, procesamiento de imágenes,
  expresiones regulares y pruebas unitarias. Contiene más de ochenta bibliotecas individuales.

  Se utiliza varias veces en el proyecto y se puede usar para más cosas si es necesario.

  > [**Cómo descargar e instalar**][Boost-tutorial]
  >
  > [**Wiki para más información**][Boost-wiki]
  >
  > [**Enlace de descarga**][Boost-download]


- #### CLion (Opcional pero muy recomendado)
  Para compilar y editar el código se ha utilizado CLion. Facilita todas las herramientas necesarias para el proyecto,
  como CMake, ninja, mingw, el compilador y el depurador. No es necesario usar CLion, pero es muy recomendable.

  > [**Enlace de descarga**][CLion-download]
  >
  > [**Wiki para más información**][CLion-wiki]

- #### MinGW/GNU Compiler Collection (GCC)

  Para ejecutar nuestro código, necesitaremos utilidades GNU. Esto contiene numerosos compiladores para varios lenguajes
  (por ejemplo, Fortran, C++, etc.) clasificados como el **GNU Compiler Collection (GCC)** y sus respectivos
  depuradores.

MinGW incluye una versión del **GNU Compiler Collection (GCC)**, GNU Binutils para Windows (ensamblador, enlazador,
gestor de archivos), un conjunto de archivos de encabezado específicos de Windows y bibliotecas de importación estáticas
que permiten el uso de la API de Windows, una versión nativa de Windows del depurador GNU del Proyecto GNU y utilidades
misceláneas.

> [**Enlace de descarga (Instalador)**][Mingw-download-installer]
>
> _**IMPORTANTE:** DEBE SELECCIONAR x86_64 (que es de 64 bits) **NO** i686 (que es de 32 bits)_
>
> En caso de que el instalador no funcione (lo cual es probable):
>
> [**Enlace de descarga (carpeta con versión de 64 bits)**][Mingw-download-folder]
>
> _**CÓMO INSTALAR:**_
> - Descomprime la carpeta, cópiala en algún lugar lógico (por ejemplo `C:/MinGW` o `C:/Program Files/MinGW`).
> - Agrega la carpeta bin a la ruta de las Variables de Entorno.<br><br>
>
>
> [**Wiki de MinGW para más información**][Mingw-wiki]

- #### **CMake**
  CMake es una familia de herramientas de código abierto y multiplataforma diseñada para construir, probar y empaquetar
  software. CMake se usa para controlar el proceso de compilación de software utilizando archivos de configuración
  simples, independientes de la plataforma y del compilador, y generar archivos makefiles y espacios de trabajo nativos
  que se pueden usar en el entorno del compilador de tu elección.

  > [**Enlace de descarga**][CMake-download]
  >
  > [**Wiki para más información**][CMake-wiki]

### Instalación

Aquí hay una guía paso a paso sobre cómo instalar el proyecto.

#### Instalación con CLion

1. Clona el repositorio
   ```sh
   git clone https://github.com/valydumitru01/GLESC.git
    ```
2. Abre el proyecto con CLion
3. Prepara las dependencias del proyecto con CLion o tu IDE preferido
4. Compila el proyecto con CMake
5. Ejecuta el proyecto

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<!-- USAGE EXAMPLES -->

## Uso

La siguiente sección está dedicada a explicar cómo usar el motor. Trataré de ejemplificar cómo crear un videojuego
utilizando el motor con el juego actualmente implementado (Dispara al pollo).

> **Nota importante:** Este motor está codificado de forma rígida, no hay programación basada en datos. Esta fue una
> elección consciente dadas las restricciones. Entonces, un gran problema al usar este motor es tener que esperar todos
> los tiempos de compilación para cada cambio menor.

> **Nota importante 2:** Hay un uso intensivo de cadenas de texto en el motor. Esto se debe a la falta de tiempo para
> implementar un mejor sistema. Y también, es muy útil para depuración y UX. Pero no es la mejor práctica por razones de
> eficiencia. En un motor normal, orientado a datos, las cadenas serían solo datos y no formarían parte del código
> compilado o la lógica.

### Creando un nuevo juego (o escena)

De hecho, la única función de la clase `Game` es manejar las escenas. Así que realmente no necesitas tocar la clase
`Game` más que para insertar las escenas que necesitas.

Para crear una nueva escena, necesitas crear una nueva clase que herede de la clase `Scene`. Puedes ver un ejemplo de
esto en la clase `ShootTheChickenGame`.
**Cómo registrar una escena:**

```c++
void Game::init() {
    registerScene<Default>(Default::getSceneName());
    registerScene<TerrainGeneratorGame>(TerrainGeneratorGame::getSceneName());
    registerScene<ShootTheChickenGame>(ShootTheChickenGame::getSceneName());
    sceneManager.switchScene(ShootTheChickenGame::getSceneName());
}
```

![Scene creation](doc/images/scene-creation-folder.png)

**Ejemplo de una clase de escena:**

```c++
class ShootTheChickenGame : public GLESC::Scene::Scene {
public:
SCENE_DEFINITION(ShootTheChickenGame)
...
};
```

Una vez que tengas tu escena definida y registrada, puedes comenzar a personalizarla. Puedes agregar entidades,
componentes, sistemas, etc. Las siguientes secciones explicarán cómo aprovechar todas las características del motor
GLESC.

#### Creando una entidad

Las entidades son los objetos principales en el motor. Pueden parecer "contenedores" para componentes, pero en realidad
son solo IDs envueltos. Los creas con un nombre y una metadata. Ese nombre luego se puede recuperar para obtener la
entidad. Solo puedes establecer la metadata de instancia, de esta manera el nombre de la entidad se incrementa
automáticamente en uno, por lo que no tienes que preocuparte por el nombre de la entidad. No tiene otro propósito que
ese.

**Ejemplo de creación de entidad:** _(Extraído de ShootTheChickenGame, cómo se crearon los pollos)_

```c++
void ShootTheChickenGame::generateChickenEntities() {
    int numChickens = 10;
    chickens.clear();
    for (int i = 0; i < numChickens; i++) {
    Transform::Position position = generateChickenPosition();
    ECS::Entity chicken = createEntity("chicken", {EntityType::Instance});
    chicken.addComponent<ECS::TransformComponent>();
    chicken.addComponent<ECS::RenderComponent>();
    chicken.addComponent<ECS::PhysicsComponent>();
    chicken.addComponent<ECS::CollisionComponent>();
    auto& transform = chicken.getComponent<ECS::TransformComponent>().transform;
    chicken.getComponent<ECS::TransformComponent>().transform.setPosition({position});
    chicken.getComponent<ECS::RenderComponent>().copyMesh(chickenMesh);
    chicken.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
    chicken.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
    chicken.getComponent<ECS::PhysicsComponent>().physics.setAffectedByGravity(true);
    transform.setPosition({transform.getPosition().getX(), 100, transform.getPosition().getZ()});
    chicken.getComponent<ECS::PhysicsComponent>().physics.setMass(5);
    chickens.push_back(chicken.getID());
}
}
```

Para crear una entidad, necesitas llamar a `createEntity("name", EntityMetadata)`. Después de eso, solo necesitas
adjuntar los componentes y modificarlos directamente.

**Ejemplo de recuperar una entidad:** _(Extraído de ShootTheChickenGame, cómo se recuperó la entidad del jugador)_

```c++
ECS::Entity player = getEntity("player");
```

Para recuperar una entidad, solo necesitas llamar a `getEntity("name")`. Esto devolverá la entidad con ese nombre.

#### Componentes

Actualmente, el motor tiene los siguientes componentes:

- TransformComponent
- CollisionComponent
- InputComponent
- LightComponent
- PhysicsComponent
- RenderComponent

> **Nota:** También tiene estos otros componentes, pero no deben usarse ya que el motor no admite actualmente más de
> uno de cada tipo, y están codificados rígidamente en el motor.
> - CameraComponent
> - SunComponent
> - FogComponent

Cada uno define un aspecto diferente de la entidad.

##### TransformComponent

El `TransformComponent` se utiliza para definir la posición, rotación y escala de la entidad. Se utiliza para definir la
posición de la entidad en el mundo.

##### CollisionComponent

El `CollisionComponent` almacena el colisionador de la entidad. Puedes definir el volumen delimitador de la entidad y
el motor manejará las colisiones por ti. También puedes establecer la función de devolución de llamada de colisión para
manejar los eventos de colisión. Incluso puedes establecer una devolución de llamada de colisión para un colisionador
específico (una entidad específica).
> Nota: Puedes establecer el volumen delimitador del colisionador para ajustar la malla de la entidad utilizando:
> ```
> c++
> chicken.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
>            chicken.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
> ```

**Ejemplo de creación de componente de colisión:** _(Extraído de ShootTheChickenGame, cómo se creó la colisión de la
bala)_

```c++
bullet.addComponent<ECS::CollisionComponent>();
bullet.getComponent<ECS::CollisionComponent>().collider.setBoundingVolume(
bullet.getComponent<ECS::RenderComponent>().getMesh().getBoundingVolume());
bullet.getComponent<ECS::CollisionComponent>().collider.setCollisionCallback(
    [bulletID, this](Physics::Collider& otherCollider) {
        collisionCallback(bulletID, otherCollider);
    });
```

##### PhysicsComponent

El `PhysicsComponent` se utiliza para definir las fuerzas, aceleración, velocidad, masa, etc. de la entidad. Realmente
se encarga de actualizar la posición de la entidad en función de las fuerzas aplicadas a ella. Puedes establecer las
fuerzas, aceleración, etc. de la entidad en cualquier momento.

##### RenderComponent

El `RenderComponent` almacena la malla y el material de la entidad. Puedes construir la malla y establecer las
propiedades del material de la entidad. El motor se encargará del renderizado por ti. La malla es un poco complicada,
así que la explicaré en la siguiente sección.

###### Mesh

La malla es una clase que almacena los vértices, normales, índices y texturas (aún no implementadas) de la entidad.
**Construyendo una malla**

**Ejemplo de creación de malla:** _(Extraído de ShootTheChickenGame, cómo se creó la malla del jugador)_

```c++
Render::ColorMesh playerGun = Render::MeshFactory::cuboid(0.5f, 0.5f, 5, Render::ColorRgb::Brown);
Render::ColorMesh playerGunHandle = Render::MeshFactory::cuboid(0.5f, 0.5f, 3, Render::ColorRgb::DarkBrown);
Transform::Transformer::translateMesh(playerGunHandle, {0, -0.5, 1.5});

Render::ColorMesh playerHand = Render::MeshFactory::cuboid(0.5f, 0.5f, 5, Render::ColorRgb::ClearSkin);
Transform::Transformer::rotateMesh(playerHand, {-25, -45, 0});
Transform::Transformer::translateMesh(playerHand, {-0.3, -0.55, 1});

playerGun.startBuilding();
playerGun.attachMesh(playerGunHandle);
playerGun.attachMesh(playerHand);
playerGun.finishBuilding();

// Rotate the gun to the left
Transform::Transformer::rotateMesh(playerGun, {25, 25, 0});
// Lift the gun to the player's hands
Transform::Transformer::translateMesh(playerGun, {1.3, -1.5, -3});
playerMesh.startBuilding();
playerMesh.attachMesh(playerGun);
playerMesh.finishBuilding();
```

Para construir una malla, necesitas utilizar la clase `MeshFactory` para crear formas básicas (o bloques de
construcción).
Luego, puedes usar la clase `Transformer` para traducir o rotar la malla. Finalmente, puedes adjuntar las mallas entre
sí para crear una malla más compleja.
> **Nota:** Adjuntar mallas de esta manera es un poco complicado y no es fácil de usar, pero esta es la única forma de
> hacerlo por ahora. Los cargadores o constructores de mallas aún no están implementados. Como se indicó anteriormente,
> no hay programación basada en datos en el motor.

###### Materiales

Los materiales son bastante fáciles de entender y usar. Cada componente de render tiene un material, y cada material
tiene un conjunto de miembros de función que definen las propiedades del material.
**Propiedades del material:**

```c++
void setDiffuseColor(const ColorRgb& diffuseColor) { this->diffuseColor = diffuseColor; }
void setDiffuseIntensity(const float diffuseIntensity) { this->diffuseIntensity.set(diffuseIntensity); }
void setSpecularColor(const ColorRgb& specularColor) { this->specularColor = specularColor; }
void setSpecularIntensity(const float specularIntensity) { this->specularIntensity.set(specularIntensity); }
void setEmissionColor(const ColorRgb& emissionColor) { this->emissionColor = emissionColor; }
void setEmissionIntensity(const float emmissionIntensity) { this->emissionIntensity.set(emissionIntensity); }
void setShininess(const float shininess) { this->shininess.set(shininess); }
```

> **Nota:** No todas las propiedades hacen algo. La intensidad y el color de emisión no funcionan. El resto debería
> funcionar bien.
<p align="right">(<a href="#readme-top">back to top</a>)</p>

##### InputComponent

El `InputComponent` se utiliza para definir las entradas de la entidad. Es bastante intuitivo y fácil de usar.
Básicamente, suscribes la entidad a una tecla (con su acción) y defines una función de devolución de llamada para
manejar el evento de entrada. También puedes anular la suscripción de la entidad de una tecla.

**Ejemplo de creación de componente de entrada:** _(Extraído de ShootTheChickenGame, cómo se creó la entrada del
jugador)_

```c++
getCamera().getEntity().getComponent<ECS::InputComponent>().input.unsubscribeKey(
    {Input::Key::SPACE, Input::KeyAction::ONGOING_PRESSED});
getCamera().getEntity().getComponent<ECS::InputComponent>().input.unsubscribeKey(
    {Input::Key::LEFT_SHIFT, Input::KeyAction::ONGOING_PRESSED});
getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
    {Input::Key::LEFT_CLICK, Input::KeyAction::ONCE_PRESSED}, shootBulletAction);
getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
    {Input::Key::SPACE, Input::KeyAction::ONCE_PRESSED}, jumpAction);

getCamera().getEntity().getComponent<ECS::InputComponent>().input.subscribeKey(
{Input::Key::R, Input::KeyAction::ONCE_PRESSED}, {
    [&]()-> void {
        if (getWindow<ShootTheChickenHUD>(statsWindow).getAmmunition() == 0) {
            switchScene<ShootTheChickenGame>();
        }
    }
});
```

> **Nota:** Probablemente necesitarás anular la suscripción de las teclas actuales de la entidad de la cámara. Esto se
> debe a que la cámara tiene un conjunto de comportamientos predeterminados que es posible que no desees. También
> puedes simplemente crear un nuevo componente de entrada y reemplazar el anterior.

##### LightComponent

El `LightComponent` le da una luz puntual a la entidad. La luz puntual se renderizará en la posición del transform de
la entidad. Si la entidad también tiene una malla, la luz se renderizará en el centro de la malla. Así que probablemente
no se verá. Puedes establecer el color, la intensidad y el radio de la luz.

**Ejemplo de creación de componente de luz:** _(Extraído de ShootTheChickenGame, cómo se creó la luz de la bala)_

```c++
bullet.addComponent<ECS::LightComponent>();
bullet.getComponent<ECS::LightComponent>().light.setColor(Render::ColorRgb::Yellow);
```

Como puedes ver, es bastante simple.

##### SunComponent

Como mencioné anteriormente, no es necesario usar estos componentes. Pero necesitas entender cómo usarlos para cambiar
la cámara, el sol y la niebla.

El componente de sol se utiliza para definir la difusión difusa del sol y la difusión difusa ambiental.
**Ejemplo de modificación del componente de sol** _(Extraído de ShootTheChickenGame, cómo se modificó el sol)_

```c++
getEntity("sun").getComponent<ECS::SunComponent>().sun.setIntensity(0.4f);
getEntity("sun").getComponent<ECS::SunComponent>().sun.setColor({255, 255, 200});
getEntity("sun").getComponent<ECS::SunComponent>().sun.setDirection({-0.4, -1, -0.4});
getEntity("sun").getComponent<ECS::SunComponent>().globalAmbientLight.setIntensity(0.5);
getEntity("sun").getComponent<ECS::SunComponent>().globalAmbientLight.setColor({255, 180, 165});
```

> Esas son entidades predefinidas llamadas "sun" y "fog" que puedes modificar.

##### CameraComponent

El componente de cámara define las propiedades de la cámara, como el campo de visión, los planos cercano y lejano, y la
relación de aspecto.
Puedes definirlas fácilmente.

**Ejemplo de modificación del componente de cámara** _(Extraído de ShootTheChickenGame, cómo se modificó la cámara)_

```c++
getCamera().getEntity().getComponent<ECS::CameraComponent>().perspective.setFovDegrees(90);
```

> El componente de cámara solo contiene perspectiva, allí obtienes los atributos para modificar.

##### FogComponent

El componente de niebla define las propiedades de la niebla, como el color, la densidad y el gradiente.
También es fácil de modificar.

**Ejemplo de modificación del componente de niebla** _(Extraído de ShootTheChickenGame, cómo se modificó la niebla)_

```c++
getEntity("fog").getComponent<ECS::FogComponent>().fog.setDensity(0.3);
getEntity("fog").getComponent<ECS::FogComponent>().fog.setColor({200, 200, 170});
getEntity("fog").getComponent<ECS::FogComponent>().fog.setEnd(60);
```

#### Sistemas

Los sistemas son las clases que manejan la lógica del juego. Se encargan de actualizar las entidades, manejar las
colisiones, actualizar el renderizador, etc.
No necesitas entender los sistemas actuales, pero puedes crear tus propios sistemas para manejar la lógica de tu juego.

Cada sistema itera sobre las entidades que tienen los componentes suscritos para ese sistema. Así que si creas un
sistema
llamado `DeathSystem` y suscribes el `CollisionComponent` y el `HealthComponent`, el sistema iterará sobre todas las
entidades que tienen ambos componentes y manejará la lógica de la muerte de la entidad.

Para crear el sistema, necesitarás heredar de la clase `System` e implementar la función `update`. La función `update`
se llama en cada frame y se encarga de actualizar las entidades.
También necesitas modificar la clase `GLESC` dentro del motor para registrar el sistema.
> **Nota:** Feo, lo sé, pero no tuve tiempo de implementar un sistema de registro de sistemas.

**Cómo registrar un sistema:** _(Extraído del motor, todos los sistemas se registran aquí)_

```c++
std::vector<std::unique_ptr<ECS::System>> Engine::createSystems() {
    std::vector<std::unique_ptr<ECS::System>> systems;
    systems.push_back(std::make_unique<ECS::RenderSystem>(renderer, ecs));
    systems.push_back(std::make_unique<ECS::TransformSystem>(ecs));
    // El sistema de física debe actualizarse antes que el sistema de colisión de física
    systems.push_back(std::make_unique<ECS::PhysicsSystem>(physicsManager, ecs));
    systems.push_back(std::make_unique<ECS::PhysicsCollisionSystem>(physicsManager, collisionManager, ecs));
    systems.push_back(std::make_unique<ECS::InputSystem>(inputManager, ecs));
    systems.push_back(std::make_unique<ECS::CameraSystem>(renderer, windowManager, ecs));
    systems.push_back(std::make_unique<ECS::LightSystem>(ecs, renderer));
    systems.push_back(std::make_unique<ECS::SunSystem>(ecs, renderer));
    systems.push_back(std::make_unique<ECS::FogSystem>(renderer, ecs));
}
```

**Ejemplo de creación de sistema:** _(Extraído del motor, cómo se creó el sistema de transformación)_

```c++
namespace GLESC::ECS {
    class TransformSystem : public System {
    public:
        explicit TransformSystem(ECSCoordinator& ecs);
    void update() override;
    };
} // namespace GLESC::ECS
```

**Ejemplo de implementación de sistema:** _(Extraído del motor, cómo se implementó el sistema de transformación)_

```c++
TransformSystem::TransformSystem(ECSCoordinator& ecs) : System(ecs, "TransformSystem") {
addComponentRequirement<TransformComponent>();
}

    void TransformSystem::update() {
        for (auto& entity : getAssociatedEntities()) {
            auto& transform = getComponent<TransformComponent>(entity);
            transform.transform.setOwnerName(getEntityName(entity).c_str());
            Transform::Rotation rotation = transform.transform.getRotation();
            // Uso de fmod para evitar errores de punto flotante
            if (rotation.getX() < -360.0f)
                transform.transform.setRotation(Transform::RotationAxis::Pitch, 360.0f);
            if (rotation.getY() < -360.0f)
                transform.transform.setRotation(Transform::RotationAxis::Yaw, 360.0f);
            if (rotation.getZ() < -360.0f)
                transform.transform.setRotation(Transform::RotationAxis::Roll, 360.0f);

            if (rotation.getX() > 360.0f)
                transform.transform.setRotation(Transform::RotationAxis::Pitch, -360.0f);
            if (rotation.getY() > 360.0f)
                transform.transform.setRotation(Transform::RotationAxis::Yaw, -360.0f);
            if (rotation.getZ() > 360.0f)
                transform.transform.setRotation(Transform::RotationAxis::Roll, -360.0f);

        }
    }
```

> Como puedes ver, llamas a addComponentRequirement para suscribir el componente al sistema, luego todas las entidades
> que tienen el componente serán actualizadas por el sistema. Para actualizar las entidades, iteras sobre
> getAssociatedEntities() y actualizas las entidades.

#### HUD

El HUD es un sistema que se encarga de renderizar el HUD del juego. Utiliza ImGUI, que es una biblioteca muy poderosa.
Mi implementación solo facilita la separación de ventanas e implementa un diseño para el HUD.

Para crear una ventana HUD, necesitas crear una clase que herede de `InGameWindow` y
sobreescribir `void windowContent()`
con el contenido real de la ventana. El contenido de la ventana será renderizado por el motor para ti.

**Ejemplo de creación de ventana HUD:** _(Extraído de ShootTheChickenGame, cómo se creó la ventana de estadísticas)_

```c++
class ShootTheChickenHUD : public GLESC::InGameWindow{
public:
...
private:
void windowContent(float timeOfFrame) override;
}; // class ChickenKillCountHUD
```

**Ejemplo de implementación de ventana HUD:** _(Extraído de ShootTheChickenGame, cómo se implementó la ventana de
estadísticas)_

```c++
ShootTheChickenHUD::ShootTheChickenHUD() {
this->setSizeFraction({0.3f, 0.1f});
this->setTitle("Chicken Kill Count");
isVisible = true;
this->setLayoutPosition(GLESC::LayoutPos::BottomRight);
this->setCenter(GLESC::WindowCenter::BottomRight);
this->addFlag(ImGuiWindowFlags_NoResize);
this->addFlag(ImGuiWindowFlags_NoMove);
this->addFlag(ImGuiWindowFlags_NoCollapse);
this->addFlag(ImGuiWindowFlags_NoTitleBar);
this->addFlag(ImGuiWindowFlags_NoScrollbar);
this->addFlag(ImGuiWindowFlags_NoSavedSettings);
this->addFlag(ImGuiWindowFlags_NoBringToFrontOnFocus);
this->addFlag(ImGuiWindowFlags_NoFocusOnAppearing);
this->addFlag(ImGuiWindowFlags_NoInputs);
this->addFlag(ImGuiWindowFlags_NoBackground);
}

void ShootTheChickenHUD::windowContent(float timeOfFrame) {
ImGui::PushFont(HudLookAndFeel::get().getFont(HudLookAndFeel::get().getDefaultFont(), 30));
// Empujar el color del texto
ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Color rojo

    ImGui::Text("Chicken Kill Count: %d", chickenKillCount);
    ImGui::Text("Ammunition: %d", ammunition);
    ImGui::PopStyleColor();
    ImGui::PopFont();
}
```

Es necesario agregar las banderas de ImGui para darle a la ventana el aspecto deseado. Y también, es necesario
establecer
las funciones de diseño personalizadas para la colocación adecuada de la ventana.
Estas son todas las funciones de diseño y enumeraciones:

```c++
enum class LayoutPos {
    TopLeft,
    CenterLeft,
    BottomLeft,
    TopCenter,
    Center,
    BottomCenter,
    TopRight,
    CenterRight,
    BottomRight,
    Custom
};

enum class WindowCenter {
    TopLeft,
    CenterLeft,
    BottomLeft,
    TopCenter,
    Center,
    BottomCenter,
    TopRight,
    CenterRight,
    BottomRight
};
/**
* @brief Establecer el tamaño máximo de la ventana
* @details Si la ventana supera este tamaño, se limitará a este tamaño
*/
void setMaxSize(ImVec2 size);
/**
* @brief Establecer el tamaño mínimo de la ventana
* @details Si la ventana es más pequeña que este valor, se limitará a este tamaño
*/
void setMinSize(ImVec2 size);
/**
* @brief Establecer el tamaño de la ventana como una fracción del tamaño de la pantalla
* @details La fracción se limita entre 0.0f y 1.0f
*/
void setSizeFraction(ImVec2 fraction);
/**
* @brief Establecer la posición de la ventana como una fracción del tamaño de la pantalla.
* @details La fracción se limita entre 0.0f y 1.0f. El centro de la ventana se establece mediante la función
* setCenter. La posición modificará ese centro.
*/
void setPositionFraction(ImVec2 fraction);
/**
* @brief Establecer el centro de la ventana
* @details El centro se utiliza para calcular la posición de la ventana.
*/
void setCenter(WindowCenter center);
/**
* @brief Establecer la posición de diseño de la ventana
* @details La posición de diseño se utiliza para calcular la posición de la ventana.
*/
void setLayoutPosition(LayoutPos position);
```

#### Depuración

Durante la ejecución del juego (en modo de depuración), verás el HUD de depuración. Incluye una consola, una lista de
entidades, un inspector de la entidad seleccionada y una ventana de texto de estadísticas. Estos son muy útiles para
editar y ver cuál es la mejor manera de implementar el juego. _Pero como dije, está codificado de forma rígida, por lo
que no puedes cambiarlo, editar las entidades en medio del juego no es posible._

Para poder alternar las ventanas de depuración, la entidad de la cámara está suscrita a la tecla `LEFT CTRL`. También
está suscrita por defecto (incluso si no está en depuración) a la tecla `1` para alternar el ratón relativo.

**Vista de ventana de depuración:**
![alt text](doc/images/debug-window-view.png)

#### Sonidos

El motor tiene un sistema de sonido simple que permite reproducir sonidos y música. Puedes reproducir música en bucle,
apagarla o cambiar la música. También puedes reproducir sonidos globales o incluso reproducir sonidos en una posición
específica, convirtiéndolos en sonidos 3D.
> **Nota:** El motor utiliza la biblioteca SDL2 para reproducir sonidos.

> **Nota 2:** El sonido 3D no se probó lo suficiente, por lo que podría no funcionar como se espera.

**Ejemplo de carga de música y sonido:** _(Extraído de ShootTheChickenGame, cómo se cargaron los sonidos)_

```c++
SoundPlayer::loadSong("Chicken_Blasters.mp3", "main_song");
SoundPlayer::loadSound("chicken_shot.mp3", "chicken_shot");
SoundPlayer::loadSound("shoot.mp3", "shoot");
SoundPlayer::loadSound("chicken_idle.mp3", "chicken_idle");
```

**Ejemplo de reproducción de música y sonido:** _(Extraído de ShootTheChickenGame, cómo se reprodujeron los sonidos)_

```c++
SoundPlayer::setMusic("main_song");
SoundPlayer::playMusic();
SoundPlayer::playSound("shoot");
```

Para reproducir una canción, primero necesitas establecer la música y luego reproducirla. Para reproducir un sonido,
solo necesitas reproducirlo por nombre.

<!-- ROADMAP -->

## Hoja de Ruta

- [x] Implementar constructor CMake
- [x] Agregar capa de abstracción de API gráfica
    - [ ] Agregar soporte para Vulkan
    - [ ] Agregar soporte para DirectX
    - [ ] Agregar soporte para Metal
    - [ ] Agregar soporte para OpenGL ES
    - [x] Agregar soporte para OpenGL
    - [ ] Agregar soporte para WebGL
- [x] Crear abstracción de ventana
- [x] Crear implementación matemática personalizada
    - [x] Crear clase de vector
    - [x] Crear clase de matriz
    - [x] Crear geometría
        - [x] Crear clase de línea
        - [x] Crear clase de poliedro
        - [x] Crear clase de plano
- [x] Agregar arquitectura ECS personalizada
- [x] Agregar renderizador
    - [x] Agregar abstracción de malla
        - [x] Agregar clase de malla
        - [ ] Agregar cargador de malla assimp
        - [ ] Agregar constructor de mallas
    - [x] Agregar shaders
        - [x] Agregar reflexiones
        - [x] Agregar difusión ambiental
        - [x] Agregar difusión solar
        - [x] Agregar difusión de luz puntual
        - [ ] Agregar difusión de luz focal
        - [ ] Agregar sombras
    - [ ] Agregar post-procesamiento
    - [x] Agregar skybox
    - [ ] Agregar texturas
- [x] Agregar física
    - [x] Fuerzas, aceleración, velocidad, etc.
    - [x] Física de cuerpo rígido
    - [ ] Física de muñeco de trapo
    - [ ] Física de cuerpos blandos
    - [ ] Dinámica de fluidos
    - [ ] Física de telas
- [x] Agregar sistema de ventanas HUD (usando imgui)
- [x] Agregar colisiones
    - [x] Agregar AABB
    - [ ] Agregar OBB con SAT
    - [ ] Agregar colisionadores convexos con SAT
    - [ ] Agregar GJK para colisionadores convexos
    - [ ] Agregar quadtree u octree para fase amplia
    - [ ] Agregar colisionadores de forma de malla
- [x] Agregar entradas
- [x] Agregar sonidos
    - [x] Agregar música
    - [x] Agregar sonidos simples
    - [x] Agregar sonidos 3D
    - [x] Agregar cargador de sonidos
- [x] Agregar gestión de escenas (actualmente está codificada rígidamente)
    - [ ] Agregar serialización de escenas
    - [ ] Agregar deserialización de escenas
    - [ ] Agregar carga de escenas
    - [ ] Agregar guardado de escenas
    - [ ] Agregar editor de escenas
- [x] Agregar depuración en el juego
    - [x] Agregar HUD de depuración en el juego
        - [x] Consola
        - [x] Lista de entidades
        - [x] Inspector de entidades
        - [x] Información general de depuración (fps, llamadas de renderizado, etc.)
    - [ ] Agregar renderizado de colisionadores
    - [ ] Agregar renderizado de volúmenes delimitadores
    - [ ] Agregar renderizado de normales
    - [ ] Agregar perfilador
    - [ ] Agregar depurador de memoria
    - [ ] Agregar detector de fugas de memoria
- [x] Crear pruebas
    - [x] Pruebas unitarias
        - [x] Matemáticas
        - [x] ECS
        - [ ] Física
        - [ ] Colisiones
        - [x] Ventana
        - [ ] Renderizador
    - [x] Pruebas de integración
        - [x] ECS

Consulta los [problemas abiertos](https://github.com/othneildrew/Best-README-Template/issues) para ver una lista
completa
de características propuestas (y problemas conocidos).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->

## Contribuciones

Por ahora, soy el único colaborador de este proyecto, ya que es un proyecto final de grado. Uno de los requisitos del
proyecto final de grado es que debe ser realizado por una sola persona. Sin embargo, si deseas contribuir al proyecto,
contáctame y podemos discutirlo una vez que el proyecto haya sido presentado.

> Nota: La lista actual de colaboradores de GitHub no es precisa. Nadie ha contribuido a este proyecto aún. La razón por
> la que hay colaboradores es que he reutilizado el repositorio de otro proyecto en el que he colaborado con otras
> personas. Nada serio, pero quería aclararlo.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->

## Licencia

Distribuido bajo la Licencia MIT. Consulta [`LICENSE.txt`][license-url] para más información.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->

## Contacto

Valentin Dumitru - [Twitter: @valentindmtr115](https://twitter.com/valentindmtr115) - email: valentindmtr115@gmail.com

Enlace del proyecto: https://github.com/valydumitru01/GLESC/

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->

## Reconocimientos

Me gustaría agradecer a las siguientes personas y recursos por ayudarme con este proyecto:

* [The Cherno - OpenGL series](https://www.youtube.com/watch?v=45MIykWJ-C4&list=PLZQftyCk7_SdoVexSmwy_tBgs7P0b97yD)
* [Professor Keenan Crane - Computer Graphics course (CMU 15-462/662)](https://www.youtube.com/watch?v=W6yEALqsD7k&list=PL9_jI1bdZmz2emSh0UQ5iOdT2xRHFHL7E)
* [Austin Morlan - What is an ECS](https://austinmorlan.com/posts/entity_component_system/#what-is-an-ecs)
* [Joey de Vries - LearnOpenGL](https://learnopengl.com/)
* [Jason Gregory - Game Engine Architecture](https://www.amazon.com/Game-Engine-Architecture-Jason-Gregory/dp/1568814135)
* [Bob Nystrom - Game Programming Patterns](https://gameprogrammingpatterns.com/)
* [Google stylesheet](https://google.github.io/styleguide/c++guide.html)
* [c++ Core Guidelines](https://isoc++.github.io/c++CoreGuidelines/c++CoreGuidelines)
* [c++ best practices](https://lefticus.gitbooks.io/c++-best-practices/content/#)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template/blob/master/README.md)
* Y [a mí][My-Portfolio]! (Por poder manejar todo el estrés, trabajo duro y dedicación necesarios para finalizar este
  proyecto)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[build-with-shield]: https://img.shields.io/badge/build_with-CMake-064F8C?style=for-the-badge&logo=cmake

<!-- Build with shields -->

[c++-shield]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white

[CMake-shield]: https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white

[OpenGL-shield]: https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge&logo=opengl&logoColor=white

[SDL2-shield]: https://img.shields.io/badge/SDL2-FFCC00?style=for-the-badge&logo=sdl&logoColor=white

[GLEW-shield]: https://img.shields.io/badge/GLEW-FFCC00?style=for-the-badge&logo=glew&logoColor=white

[ImGui-shield]: https://img.shields.io/badge/ImGui-FF6F61?style=for-the-badge&logo=imgui&logoColor=white

[Mingw-shield]: https://img.shields.io/badge/Mingw-FF6F61?style=for-the-badge&logo=mingw&logoColor=white

[Boost-shield]: https://img.shields.io/badge/Boost-FF6F61?style=for-the-badge&logo=boost&logoColor=white

<!-- Tools urls -->

[c++-url]: https://cplusplus.com/

[CMake-url]: https://cmake.org/

[OpenGL-url]: https://www.opengl.org/

[SDL2-url]: https://www.libsdl.org/

[GLEW-url]: https://glew.sourceforge.net/

[GLM-url]: https://glm.g-truc.net/0.9.9/index.html

[ImGui-url]: https://github.com/ocornut/imgui/

[Mingw-url]: https://sourceforge.net/projects/mingw-w64/

[Boost-url]: https://www.boost.org/


<!-- Project's GitHub shields -->

[documentation-shield]: https://img.shields.io/badge/documentation-available-brightgreen?style=for-the-badge

[issues-shield]: https://img.shields.io/github/issues/valydumitru01/GLESC?style=for-the-badge

[forks-shield]: https://img.shields.io/github/forks/valydumitru01/GLESC?style=for-the-badge

[stars-shield]: https://img.shields.io/github/stars/valydumitru01/GLESC?style=for-the-badge

[pull-requests-shield]: https://img.shields.io/github/issues-pr/valydumitru01/GLESC?style=for-the-badge

[download-game-examples-shield]: https://img.shields.io/badge/download_game_examples-blue?style=for-the-badge


<!-- Project's GitHub urls -->

[issues-url]: https://github.com/valydumitru01/GLESC/issues/

[forks-url]: https://github.com/valydumitru01/GLESC/network/members/

[stars-url]: https://github.com/valydumitru01/GLESC/stargazers/

[pull-requests-url]: https://github.com/valydumitru01/GLESC/pulls/

[project-url]: https://github.com/valydumitru01/GLESC/

[GLESC_yt_video_url]: https://www.youtube.com/watch?v=BUtPk38Kh0Y

[download-game-examples-url]: https://github.com/valydumitru01/GLESC/releases/download/GLESC_game_examples/GLESC_games.zip

<!-- Dependencies download urls -->

[Mingw-download-installer]: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download

[Mingw-download-folder]:https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download

[CLion-download]: https://www.jetbrains.com/clion/download/

[Boost-download]: https://www.boost.org/users/download/

[CMake-download]: https://cmake.org/download/

<!-- Dependencies wiki urls -->

[Mingw-wiki]: http://mingw.org/

[CLion-wiki]: https://www.jetbrains.com/clion/

[Boost-wiki]: https://www.boost.org/

[CMake-wiki]: https://cmake.org/

<!--Installation tutorials -->

[Boost-tutorial]: https://www.boost.io/doc/user-guide/getting-started.html#:~:text=Download%20Boost%201%20Navigate%20to%20https%3A%2F%2Fwww.boost.org%2Fusers%2Fdownload%2F%20and%20under,compressed%20file%20and%20extract%20it%20to%20a%20folder.


<!-- My personal Urls -->

[My-Portfolio]: https://valydumitru01.github.io/ValentinDumitrusPortfolio/

[My-Twitter]: https://twitter.com/valentindmtr115

[My-LinkedIn]: https://www.linkedin.com/in/valentin-dumitru-a4703a211/

[My-Github]: https://github.com/valydumitru01

<!-- Misc shields -->

[game-engine-shield]: https://img.shields.io/badge/game_engine-C%2B%2B-00599C?style=for-the-badge&logo=game-engine&logoColor=white

[license-shield]: https://img.shields.io/badge/license-MIT-blue?style=for-the-badge

[version-shield]: https://img.shields.io/badge/version-0.0.1-blue?style=for-the-badge

[platform-shield]: https://img.shields.io/badge/platform-Windows-informational?style=for-the-badge

[code-style-shield]: https://img.shields.io/badge/code_style-Custom-AB47BC?style=for-the-badge

<!-- Misc variables -->

[GLESC_logo]: doc/images/GLESC_logo.png

[license-url]: LICENSE.txt

[project-version]: 0.0.1

[code-style-url]: doc/CODE_STYLE.md

[documentation-url]: doc/TFG_GLESC_Documentation.pdf

[GLESC_logo]: doc/images/GLESC_logo.png