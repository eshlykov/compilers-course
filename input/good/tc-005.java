class TestCase {
    public static void main(String[] args) {
        System.out.println(0);
    }
}

class Test extends TestCase {
    int x;
    public int Foo() {
        x = 0;
        return x;
    }
}
