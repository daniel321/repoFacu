package org.tcp1.ejemplo6;

import java.util.Random;

public class Main {
	
	private static final int CANTIDAD_ITEMS = 4;
	
	private static Random generadorRandom;

	public static void main ( String[] args ) {

		float buffer[] = new float[CANTIDAD_ITEMS];
		
		// se inicializan los valores iniciales
		generadorRandom = new Random ();
		for ( int i=0;i<CANTIDAD_ITEMS;i++ )
			buffer[i] = generadorRandom.nextFloat ();
		
		Coordinador coordinador = new Coordinador ( buffer,CANTIDAD_ITEMS );
		coordinador.procesar ();
		
		System.out.println ( "Fin del programa" );
	}

}
