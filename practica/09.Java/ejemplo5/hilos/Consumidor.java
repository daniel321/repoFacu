package org.tcp1.ejemplo5.hilos;

import org.tcp1.ejemplo5.buffer.Buffer;
import org.tcp1.ejemplo5.buffer.Semaforo;

public class Consumidor implements Runnable {
	
	private Buffer buffer;
	private Semaforo semaforoLectura;
	private Semaforo semaforoEscritura;
	private int vueltas;

	public Consumidor ( Buffer buffer,Semaforo semaforoLectura,Semaforo semaforoEscritura,int vueltas ) {
		this.buffer = buffer;
		this.semaforoLectura = semaforoLectura;
		this.semaforoEscritura = semaforoEscritura;
		this.vueltas = vueltas;
	}

	@Override
	public void run() {
		
		for ( int i=0;i<vueltas;i++ ) {
			
			// calcular valor random a dormir
			int aDormir = calcularRandom ( 1,10 );
			
			// el consumidor pide permiso para leer el valor
			System.out.println ( "Consumidor: esperando para leer" );
			semaforoLectura.p ();
			// leer el valor del buffer
			int valor = buffer.getValor ();
			System.out.println ( "Consumidor: valor leido del buffer = " + valor + " (tiempo a dormir = " + aDormir + ")" );
			// el consumidor notifica al productor que puede escribir el siguiente valor
			System.out.println ( "Consumidor: notificando al productor" );
			semaforoEscritura.v ();
			
			try {
				Thread.sleep ( aDormir*1000 );
			} catch (InterruptedException e) {}
		}
	}

	private int calcularRandom ( int max,int min ) {
		return (int)(Math.random()*(max-min))+min;		
	}
}
