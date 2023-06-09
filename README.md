# Desarrollo de BlockChain utilizando estructura de datos 
## Integrantes   
1.- Raul Bustamante  
2.- Bruno  Miranda
3.- Jorge Fernandez  


### Descripción
Este proyecto es un ejemplo de implementación de un blockchain básico que utiliza una estructura de datos específica para almacenar y gestionar las transacciones. Proporciona una representación simplificada de cómo funcionan las transacciones en un entorno de blockchain, junto con la implementación de una estructura de datos adecuada para su almacenamiento eficiente.

El objetivo principal de este ejemplo es demostrar cómo una estructura de datos puede mejorar la eficiencia y la gestión de las transacciones en un blockchain. Además de los conceptos fundamentales de las transacciones y la verificación criptográfica, este ejemplo incorpora una estructura de datos específica para la organización y el acceso rápido a las transacciones.

### Características

1.-Creación y gestión de billeteras (wallets)  
2.-Generación de transacciones  
3.-Verificación de firmas digitales  
4.-Validación y registro de transacciones en la cadena de bloques  

<!-- ## Tabla de contenidos

- [Instalación](#instalación)
- [Hash256](#Hash256)
- [Ejemplos](#ejemplos)
- [Contribución](#contribución)
- [Licencia](#licencia) -->

## Instalación

1. Clona el repositorio:

```bash
git clone https://github.com/Jorgfernvi/Blockchain-1
```

## Hash256
### Generador de hash SHA-256 para bloques de datos
Este programa implementa un generador de hash utilizando el algoritmo SHA-256 para bloques de datos. El código está escrito en C++ y utiliza la biblioteca estándar de C++.

#### Requisitos y dependencias
1.-Compilador que admita el estándar C++    
2.- Bibliotecas estándar de C++  

#### Explicación del código
El código consta de dos archivos: "main.cpp" y "block.cpp". "main.cpp" contiene la función principal y "block.cpp" implementa la clase Block.

La función generateHash calcula el hash SHA-256 para un bloque de datos proporcionado. Toma como parámetro un objeto Block<TK> y realiza los siguientes pasos:

1.- Obtiene el hash anterior y el hash actual del bloque.  
2.-Inicializa el timestamp y el patrón inicial para los hashes.  
3.-Itera hasta encontrar un valor de nonce válido que genere un hash que coincida con el patrón.  
4.-Concatena los datos del bloque, incluyendo el número de bloque, el hash anterior, el hash actual, el timestamp, el nonce y los datos adicionales.  
5.-Utiliza la función sha256 para calcular el hash SHA-256 del bloque.  
6.-Imprime el nonce encontrado y el hash resultante.  
La función sha256 implementa el algoritmo SHA-256, que divide el mensaje en bloques de 64 bytes y realiza varias operaciones para generar el hash final.  
  
  
#### Uso del código
Para utilizar el generador de hash en tu programa o proyecto, sigue estos pasos:

1.-Incluye los archivos de encabezado necesarios, como "block.h".  
2.-Crea un objeto Block<TK> con los datos que deseas procesar.  
3.-Llama a la función generateHash pasando el objeto Block<TK> como parámetro.  
4.-El resultado se mostrará en la salida estándar.  
  
#### Bloque
  La clase Block es una implementación de un bloque en una cadena de bloques, que se utiliza comúnmente en tecnologías como blockchain. Un bloque contiene un conjunto de registros y tiene propiedades como un índice, un código hash, un código hash anterior, un nonce, entre otros.
  
  
#### Atributos de la clase Block
**index**: Representa el índice del bloque en la cadena.  
**nonce**: Es un número utilizado en la minería de bloques para encontrar un código hash válido.  
**records**: Un contenedor de registros que se almacenan en el bloque.  
**string_records**: Una representación en cadena de los registros dentro del bloque.  
**current_hash_code**: El código hash actual del bloque.  
**previous_hash_code**: El código hash del bloque anterior en la cadena.  
**record_index**: El índice actual utilizado para insertar registros.  
**capacity**: La capacidad máxima de registros que puede almacenar el bloque.  

  
  
#### Métodos de la clase Block
**setIndex(int index):** Establece el índice del bloque.  
**setPreviousHashCode(string previous_hash_code):** Establece el código hash del bloque anterior.  
**getIndex():** Devuelve el índice del bloque.  
**getNonce():** Devuelve el nonce del bloque.  
**getDatos():** Devuelve los datos del bloque.  
**getHashCode():** Devuelve el código hash actual del bloque.  
**getPreviousHashCode():** Devuelve el código hash del bloque anterior.  
**getSize():** Devuelve la cantidad de registros almacenados en el bloque.  
**getCapacity():** Devuelve la capacidad máxima del bloque.  
insert(Record* new_record): Inserta un nuevo registro en el bloque.  
**generateHash():** Genera el código hash del bloque utilizando el algoritmo SHA-256.  

  
### Uso de la clase Block
Para utilizar la clase Block, se siguen los siguientes pasos:

Crear un objeto Block, por ejemplo: Block<Record> block;  
Establecer el índice y el código hash del bloque anterior utilizando los métodos setIndex() y setPreviousHashCode(), respectivamente.  
Insertar registros en el bloque utilizando el método insert(), pasando un puntero al registro.  
Generar el código hash del bloque utilizando el método generateHash().  
Acceder a los atributos del bloque según sea necesario, utilizando los métodos getIndex(), getHashCode(), getNonce(), etc.    
  
#### Blockchain
  En el archivo proporcionado se muestra la implementación de una clase Blockchain en C++. El código incluye las definiciones de las funciones miembro de la clase Blockchain, así como algunas funciones auxiliares.
  
  
#### Atributos de la clase Blockchain
1.- map<size_t, Block<T>*> block_map: Este atributo es un mapa que almacena los bloques de la cadena de bloques. El índice del bloque se utiliza como clave y se mapea a un puntero al bloque correspondiente. Permite un acceso eficiente a los bloques de la cadena.

2.- string string_records: Este atributo es una cadena que almacena una representación en formato de cadena de todos los registros agregados a la cadena de bloques. Se utiliza para calcular el hash del bloque en el proceso de minería.

3.- Block<Record>* last_block: Este atributo es un puntero al último bloque agregado a la cadena de bloques. Se utiliza para mantener un registro del bloque anterior al agregar nuevos bloques.

4.- int record_index: Este atributo mantiene el índice del registro actual en la cadena de bloques. Se utiliza para realizar un seguimiento de la posición al agregar nuevos registros.

5.- int block_index: Este atributo mantiene el índice del bloque actual en la cadena de bloques. Se utiliza para asignar índices a los nuevos bloques al agregarlos.

6.- int block_size: Este atributo indica el tamaño máximo de registros que puede contener un bloque. Determina cuántos registros se deben agregar antes de crear un nuevo bloque.  

  
  La funcionalidad principal de la clase Blockchain es almacenar y gestionar bloques de registros en una cadena de bloques. Proporciona métodos para agregar registros y bloques, realizar la minería de bloques, y buscar registros en la cadena de bloques según criterios como el rango de monto, rango de fechas, remitente y destinatario. También se incluyen métodos para obtener información sobre el tamaño del bloque y acceder a bloques específicos por su índice.
  
 #### Funcionalidades del blockchain
1.-  Agregar un nuevo registro a la cadena de bloques utilizando la función addRecord.
2.-  Agregar un nuevo bloque a la cadena de bloques utilizando la función addBlock.
3.-  Realizar la minería de un bloque (calcular su hash) utilizando la función mine.
4.-  Obtener el tamaño de bloque actual utilizando la función getBlockSize.
5.-  Obtener un bloque específico por su índice utilizando la función getBlock.
6.-  Realizar búsquedas en la cadena de bloques por rango de monto, rango de fechas, remitente o destinatario utilizando las funciones searchByAmountRange, searchByDateRange, searchByRemitente y searchByDestinatario, respectivamente.
  
 ### Funcionalidad del proyecto Main.cpp
  
1.- Abre el archivo "datos_proyecto.csv" para leer los datos de entrada.

2.- Crea una instancia de la clase Blockchain<Record> llamada chain para almacenar la cadena de bloques.

3.- Crea una instancia de la clase Block<Record> llamada block para almacenar los registros en un bloque antes de agregarlo a la cadena de bloques.

4.- Crea una instancia de la clase ChainHash<string, Record*> llamada myhash para almacenar registros en una tabla hash basada en el remitente.

5.- Crea una instancia de la clase MaxHeap<Record*> llamada maxHeap para almacenar registros en un montón máximo basado en el monto.

6.- Lee el archivo línea por línea y divide cada línea en elementos separados por comas. Cada línea representa un registro con información de remitente, destinatario, monto y fecha.

7.- Si el tamaño del bloque alcanza su capacidad máxima, se agrega el bloque actual a la cadena de bloques y se crea un nuevo bloque.

8.- Para cada registro leído, se crea una instancia de la clase Record, se asignan los valores correspondientes y se inserta en el bloque actual.Además de insertar el registro en el bloque, se agrega el registro a la tabla hash myhash usando el remitente como clave y el puntero al registro como valor.

9.- También se inserta el registro en el montón máximo maxHeap utilizando el monto como clave y el puntero al registro como valor.

10.-  Se almacenan los datos en un vector bidimensional data que contiene todas las filas y columnas del archivo CSV.

A continuación, se realizan varias búsquedas en la cadena de bloques y en las estructuras de datos auxiliares:
a. Se realiza una búsqueda en chain por rango de monto, utilizando los valores rango_ini y rango_fin especificados.  
b. Se realiza una búsqueda en chain por rango de fechas, utilizando las fechas "01/01/2023" y "12/31/2023".  
c. Se realiza una búsqueda en myhash por remitente, utilizando el nombre "Rina Lowe".  
d. Se realiza una búsqueda en myhash por destinatario, utilizando el nombre "Jordan Tyler".  
e. Se extrae el máximo valor del maxHeap, que corresponde al registro con el monto más alto.  

11.- Finalmente, se devuelve el valor 0 para indicar una finalización exitosa del programa.  

En resumen, el código lee los datos de un archivo CSV, los organiza en bloques y los almacena en una cadena de bloques. Luego, realiza diversas búsquedas en la cadena de bloques y en las estructuras de datos auxiliares para recuperar registros según diferentes criterios.
