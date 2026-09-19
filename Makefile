GCC_FLAGS=-Wall -Wconversion -Wtype-limits -pedantic -Werror -g
#Creo un nombre por predeterminado por si el usuario se olvida de mandarlo por parametro
NOMBRE ?= programa
NOMBRE_TEST ?= testing


manual:
	@echo "=========================================================================="
	@echo "              MANUAL DE USO Y COMANDOS DEL PROGRAMA"
	@echo "==========================================================================\n"
	@echo "    1. Compilación:"
	@echo "    • make compile               -> Compila el programa principal (Por defecto: $(NOMBRE))"
	@echo "    • make compile NOMBRE=nombre -> Compila asignándole un nombre personalizado"
	@echo "    • make compile_test          -> Compila el set de pruebas (Por defecto: $(NOMBRE_TEST))\n"
	@echo "    2. Ejecución:"
	@echo "    • ./$(NOMBRE) <operador> <conjunto> ...  -> Ejecuta el programa principal (requiere compilar antes)"
	@echo "    • make test                             -> Ejecuta las pruebas unitarias\n"
	@echo "   >Nota: Recuerda compilar siempre antes de ejecutar el progrma."
	@echo "=========================================================================="

compile:
	gcc $(GCC_FLAGS) main.c src/*.c -o $(NOMBRE)
	@echo "\nSe ha creado un archivo .o llamado $(NOMBRE)\n\nSi quieres saber como ejercutarlo escribe el siguiente comando:"
	@echo "make test\n"

compile_test:
	gcc ${GCC_FLAGS} pruebas/*.c src/*.c -o ${NOMBRE_TEST}
	@echo "La compilación ha sido exitosa!"

test:
	./${NOMBRE_TEST}
	