class TestCase {
    public static void main(String[] args) {
        System.out.println(new TestCaseAtomic().Test());
    }
}

class TestCaseAtomic {
    public int Test() {
        return new UserType() * new int[3];
    }
}

class UserType {
}
