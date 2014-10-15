#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <signal.h>

// TODO hacer configurable

const char* ArchBoleteriaCerrada = "common/Constants.h";
char CodeBoleteriaCerrada = 'z';

static int SigClienteVendedor = SIGUSR1;
static int SigClienteCalesita = SIGUSR1;
static int SigTerminoCalesita = SIGUSR1;

static int SigQuit = SIGUSR2;

const char* ARCHCOMUNICACIONCLIENTEVENDEDOR = "/tmp/atendiendo";
const char* ARCHCOMUNICACIONCLIENTEVENDEDOR2 = "/tmp/atendiendo2";

const char* ArchColaBoletos = "/tmp/colaBoletos";
const char* ArchColaCalesita = "/tmp/colaCalesita";

const char* ArchaCajaVendedor = "/tmp/cajavendedor";
const char* ArchCajaAdmin = "/tmp/cajaadmin";
const char* ArchGenteEsperandoParaUsarCaja = "/tmp/esperandocaja";

static int QuieroConsultarCaja = -1;

#endif










