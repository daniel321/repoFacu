algunos detalles de implementacion:

1) No pude lograr que todos los sean de una línea, pero poniendo como objetivo minimizar la cantidad de líneas por método pude dejarlo en 2 lineas por método.

2.1) Fue necesario el uso de operadores condicionales principalmente por que no tengo ningúna otra forma de detectar que la cola esta vacía o una variable está en null y actuar en consecuéncia sin un operador de ese tipo, se me había ocurrido intentar algo con sobrecarga de métodos, pero desgraciadamente null no tiene tipo en java...

2.2) Use principalmente el tri-ario: ()?():() 
lo elegí ya que es mas compacto, lo que ayuda al objetivo de minimizar la cantidad de lineas por método, pero puede reemplazarse sencillamente por un par de lineas usando if's

3) Fue necesario implementar un método aparte para el cálculo del tamaño de la cola, para ahorrarme las líneas de size++,size-- al agregar y borrar elementos, personalmente prefiero mantener el tamaño de la cola como un atributo y asi evitarme el recalcularlo cada vez que lo necesite (siendo esto ineficiente si la cola crece demasiado), pero le di prioridad al objetivo de minimizar las lineas.

aparte de otra forma solo tendria que buscar y tratar de "comprimir" los metodos de la cola implementada en informatica 2 (en otra facu), algoritmos 1, algoritmos 2, quizas modificar la lista de algoritmos 3, la que nos hicieron hacer como herramienta para el tp1 de taller o la del tp0 de datos (aunque esa era en archivos).... (desde ningún punto de vista les estoy hechando la culpa de ello a ustedes, pero es medio molesto)

