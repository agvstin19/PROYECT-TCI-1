# by GUAYMAS AGUSTIN FABRIZZIO, LAMAS TORRES ERICK DIEGO, RIVERA YULETHSY KATERINE
##Informe sobre la representación de delta en C

###En este informe voy a analizar distintas formas de representar la función de transición delta de un autómata utilizando el lenguaje C, con el objetivo de elegir la alternativa más conveniente para el proyecto de conversión y simulación de autómatas.  Las propuestas analizadas fueron las siguientes:

##1. Lista de transiciones:
###Consiste en almacenar todas las transiciones en una lista global con la forma (estado origen, símbolo, estado destino). Su principal ventaja es que resulta sencilla de implementar y de entender. Sin embargo, cada búsqueda requiere recorrer la lista, por lo que el tiempo de acceso aumenta a medida que crece la cantidad de transiciones.

##2. Indexado por estado: 
###Cada estado mantiene su propia lista de transiciones. Esta alternativa permite acceder de forma más organizada a la información y se adapta tanto a autómatas finitos deterministas como no deterministas. Además, facilita los procesos de simulación y determinación.

##3. Matriz dispersa: 
###Se basa en una estructura similar a una tabla de estados y símbolos. Permite accesos rápidos, pero puede consumir mucha memoria cuando existen muchas posiciones vacías.

##4. Delta funcional: 
###Representa directamente el resultado de la función delta(q,a). Desde el punto de vista teórico es una solución elegante, aunque su implementación resulta más compleja y menos práctica para este proyecto.

##5. Estados compuestos: 
###Esta representación es útil para el autómata obtenido luego de la determinación. Sin embargo, no resulta adecuada para representar el autómata original.


###Después de comparar las distintas alternativas, considero que la mejor opción es el indexado por estado. La principal razón es que permite trabajar de forma natural tanto con AFD como con AFND utilizando la misma estructura de datos. Además, simplifica la implementación de algoritmos relacionados con la determinación y mantiene el código más ordenado. En conclusión, la representación mediante indexado por estado es la alternativa más conveniente para el desarrollo del proyecto, ya que ofrece un buen equilibrio entre eficiencia, claridad y facilidad de mantenimiento. 
