package org.tcp1.ejemplo5.hilos;

import org.tcp1.ejemplo5.buffer.Buffer;
import org.tcp1.ejemplo5.buffer.Semaforo;

public class Productor implements Runnable {
	
	private Buffer buffer;
	private Semaforo semaforoLectura;
	private Semaforo semaforoEscritura;
	private int vueltas;


	public Productor ( Buffer buffer,Semaforo semaforoLectura,Semaforo semaforoEscritura,int vueltas ) {
		this.buffer = buffer;
		this.semaforoLectura = semaforoLectura;
		this.semaforoEscritura = semaforoEscritura;
		this.vueltas = vueltas;
	}

	@Override
	public void run() {
		
		for ( int i=0;i<vueltas;i++ ) {
			
			// calcular valor random para guardar en el buffer
			int aGuardar = calcularRandom ( 1,100 );
			
			// calcular valor random a dormir
			int aDormir = calcularRandom ( 1,10 );
			
			// el productor pide permiso para escribir en el buffer
			System.out.println ( "Productor: esperando para escribir" );
			semaforoEscritura.p ();
			buffer.setValor ( aGuardar );
			System.out.println ( "Productor: valor guardado en el buffer = " + aGuardar + " (tiempo a dormir = " + aDormir + ")" );
			// el productor notifica al consumidor que puede leer
			System.out.println ( "Productor: notificando al consumidor" );
			semaforoLectura.v ();
			
			try {
				Thread.sleep ( aDormir*1000 );
			} catch (InterruptedException e) {}
			
		}
	}

	private int calcularRandom ( int max,int min ) {
		return (int)(Math.random()*(max-min))+min;		
	}
}
