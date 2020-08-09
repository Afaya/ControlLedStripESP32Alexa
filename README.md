# ControlLedStripESP32Alexa

Este proyecto pretende ser algo muy simple: conectar una tira de leds a una placa ESP32 y controlar su encendido desde Amazon Echo. Para ello buscamos información en diferentes lugares porque no encontramos a la primera nada que nos funcionase directamente. 

Lo primero de todo es configurar el IDE de Arduino, instalando en Gestor de Tarjetas ESP32 (Archivo > Preferencias > Gestor de urls). Así podremos seleccionar como Herramientas > Gestor de tarjetas, la ESP32 Dev Module. También es importante seleccionar en Herramientas > Upload Speed la de 115200.

A continuación hay que instalar las siguientes bibliotecas: Adafruit_NeoPixel, Wifi y FauxmoESP, bien a través de Programa > Incluir librería > Administrar Bibliotecas o bien de forma manual descargándolas y añadiendólas como Biblioteca Zip en Programa > Incluir Librería. Importante que por defecto viene configurada una de wifi y a nosotros nos dió problemas, tuvimos que eliminarla y dejar instalada sólo la que usamos.

Partes importantes de nuestro programa:

Adafruit_NeoPixel strip(60, LED_PIN_STRIP, NEO_GRB + NEO_KHZ800) --> aquí indicamos que la tira de leds consta de 60 leds, y que está conectada al pin LED_PIN_STRIP, los otros dos paramétros son de configuración.

fauxmo.addDevice("Led") --> Aquí indicamos el nombre con el que reconocerá Alexa a nuestro programa.

Dentro del setup en  fauxmo.onSetState, es dónde configuramos la acción que ejecutará sobre los leds. Aquí cuidado porque probamos diferentes aproximaciones, incluida la de ir iniciándolos en forma de ola con un bucle, pero se demoraba suficiente tiempo para que no le llegase a Alexa la confirmación de que lo había hecho y se producía un error. Para solucionarlo, lo que hacemos en el setup es poner una variable a true o false según corresponda y en el loop dependiendo de esa variable lanzará o no un método.

Dentro del loop simplemente tenemos controlTestLed() --> un método de prueba en el que tratamos de activar un pin led para probar que todo va bien y fauxmo.handle(), que lanza las acciones incluidas en el setup. Después de este método dependiendo del valor de la variable booleana que seteamos en el setup, lanzamos o no que encienda las luces como si fuese una ola.

Por último, cuando trabajas con la ESP32 es necesario que tras compilar y al subir un fichero a la placa, que cuando aparezca por consola Connecting se apriete el botón boost de la placa, esto hará que se suba correctamente. Una vez esté cargado al 100% es necesario presionar el botón reset. Otra solución sería añadirle un condensador a la placa, pero nosotros para esta prueba no lo usamos. 



