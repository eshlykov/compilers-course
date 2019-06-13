class TestCase {
    public static void main(String[] args) {
        System.out.println(0);
    }
}

class Test1 {
    int x;
}

class Test2 extends Test1 {
    boolean x;
    public boolean Foo() {
    	return x;
    }
}