CC=gcc

CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0` -o3 -lncurses

LDFLAGS=`pkg-config --libs glib-2.0` -lm -lncurses


programa-principal: src/main.o src/query1.o src/query2.o src/query3.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/batch.o src/interactive.o src/func.o src/loadfiles.o src/datastruc.o src/rides.o src/users.o src/drivers.o
	@mkdir -p Resultados
	$(CC) $^ $(LDFLAGS) -o $@

programa-testes: src/main_testes.o src/query1.o src/query2.o src/query3.o src/query4.o src/query5.o src/query6.o src/query7.o src/query8.o src/query9.o src/batche.o src/func.o src/loadfiles.o src/datastruc.o src/rides.o src/users.o src/drivers.o
	@mkdir -p Resultados
	$(CC) $^ $(LDFLAGS) -o $@

src/%.o: src/%.c


clean:
	rm -f programa-principal src/*.o
	rm -f programa-testes src/*.o
	rm -r Resultados
