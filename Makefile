all: compile run clean

compile: main.c file_ops.c query_products.c
	@gcc main.c file_ops.c query_products.c check_stock_status.c brand_stock_control.c -o exec

run: exec
	@./exec

clean:
	@rm -f exec