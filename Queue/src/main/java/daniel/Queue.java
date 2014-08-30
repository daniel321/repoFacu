package daniel;

public interface Queue {
	boolean isEmpty();
	int size();
	void add(Object item); //agregar un item
	Object top(); 	// retornar el primer item, lanzar excepción si esta vacio.
	void remove();	// remover el primer elemento, lanzar excepción si esta vacío.
}
