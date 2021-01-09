
test-build:
	gcc test/test.c test/unity/unity.c src/soft_tim.c -o test

test-run:
	test.exe

test-clean:
	del test.exe

test-iterate:
	del test.exe
	gcc test/test.c test/unity/unity.c src/soft_tim.c -o test
	test.exe
