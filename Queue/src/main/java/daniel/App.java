package daniel;

import static org.junit.Assert.*;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
	try{
		System.out.printf("\nhello world");
		AQueue test = new AQueue();
		test.add("hello....");
       	 	System.out.printf("\n%s\n",(String)test.top());
	}catch(AssertionError exception){}
    }
}
