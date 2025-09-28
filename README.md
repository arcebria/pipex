# 🛠️ **Proyecto pipex** 🚀

El **proyecto pipex** es un reto de 42 en el que debes recrear el comportamiento de las tuberías (`|`) de la shell de Unix.  
🧑‍💻 El objetivo es ejecutar comandos encadenados, gestionando la entrada y salida estándar entre ellos, como lo haría la shell.  
Este proyecto me permitió mejorar mis habilidades en **programación de procesos**, **gestión de archivos** y **comunicación entre programas** usando tuberías.

---

## ✨ **Lo que aprendí realizando el proyecto**

A lo largo de pipex, adquirí conocimientos clave para el desarrollo de utilidades de sistema y la gestión de procesos en C:

- 🔗 **Manejo de tuberías y procesos**  
  Aprendí a crear y gestionar **tuberías** (`pipe`) para comunicar procesos, y a usar **fork** y **execve** para ejecutar comandos como lo hace la shell.

- 🗂️ **Gestión de archivos y redirecciones**  
  Implementé la **apertura, cierre y redirección** de archivos usando `open`, `close`, `dup2`, permitiendo que los comandos lean y escriban en archivos como entrada y salida.

- 🧩 **Parámetros y parsing**  
  Desarrollé lógica para **parsear argumentos** y comandos, gestionando rutas y variables de entorno para encontrar los ejecutables correctos.

- 🧹 **Gestión de memoria y errores**  
  Me enfoqué en la **gestión de memoria dinámica** y el manejo de errores, asegurando que el programa sea robusto y eficiente.

- 📚 **Uso de librerías propias (libft)**  
  Integré funciones de mi propia librería (**libft**) para facilitar el manejo de cadenas, listas y utilidades varias.

---

## 🏁 **El resultado final**

El resultado fue una **herramienta funcional** capaz de encadenar comandos como lo haría la shell, gestionando correctamente la entrada y salida entre ellos.  
Este proyecto me permitió aprender sobre la **programación de procesos**, la **comunicación entre programas** y el **manejo avanzado de archivos** en C.  
🔓 ¡Ahora tengo una base sólida para abordar proyectos más complejos relacionados con sistemas y shells!

---

## ⚡ **Ejemplo de uso**

```sh
./pipex infile "grep hola" "wc -l" outfile