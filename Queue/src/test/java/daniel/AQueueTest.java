package daniel;

import static org.junit.Assert.*;
import org.junit.Test;

public class AQueueTest {

	@Test
	// unit test for method "top"
	public void testAddAndTop() {
		AQueue queue = new AQueue();
		
		// test top: throws exception when empty
		try{
			queue.top();
			fail();
		}catch(AssertionError exception){}
		
		queue.add(123);		
		assertEquals("test top: when only object",queue.top(),123);

		for(int i=0;i<10;i++){
			queue.add(i);
		}
		assertEquals("test top: when many objects",queue.top(),123);		

		queue.remove();
		assertEquals("test top: after removal",queue.top(),0);		
		
		for(int i=1;i<=10;i++){
			queue.remove();
		}
		
		// test top: throws exception when empty after removing all
		try{
			queue.top();
			fail();
		}catch(AssertionError exception){}
	}

	@Test
	// unit test for method "size"
	public void testSize(){
		AQueue queue = new AQueue();
		assertEquals("test size: size is 0 when created",queue.size(),0);
		queue.add(123);
		assertEquals("test size: size is 1 after adding an element",queue.size(),1);
		queue.add(345);	
		assertEquals("test size: size is 2 after adding another element",queue.size(),2);
		queue.remove();
		assertEquals("test size: size is 1 after removing an element",queue.size(),1);		
		queue.remove();
		assertEquals("test size: size is 0 after removing another element",queue.size(),0);
		
		try{
			queue.remove();	
		}catch(AssertionError exception){}
		
		assertEquals("test size: size is 0 after trying to remove when empty",queue.size(),0);
	}
	
	@Test
	// unit test for method "isEmpty"
	public void testEmpty(){
		AQueue queue = new AQueue();
		assertTrue("test empty: it's empty when created",queue.isEmpty());
		queue.add(123);
		assertFalse("test empty: it's not empty after adding an element",queue.isEmpty());
		queue.remove();	
		assertTrue("test empty: it's empty after removing the element",queue.isEmpty());

		try{
			queue.remove();	
		}catch(AssertionError exception){}
	
		assertTrue("test empty: it's empty after trying to remove when empty",queue.isEmpty());
	}	

	@Test
	// unit test for method "remove"
	public void testRemove(){
		AQueue queue = new AQueue();

		// test remove: throws exception when empty
		try{
			queue.remove();
		}catch(AssertionError exception){}

		queue.add(123);
		queue.add(456);
		queue.remove();
		
		assertEquals("test remove: removes correctly when two elements",queue.top(),456);
		queue.remove();
		assertTrue("test empty: it's empty after removing the element",queue.isEmpty());

		// test remove: throws exception when empty after removing all
		try{
			queue.remove();
		}catch(AssertionError exception){}
	}	
	
	@Test
	// complete test
	public void testComplete() {
		AQueue queue = new AQueue();
		
		try{
			queue.top();
			fail();
		}catch(AssertionError exception){}
		
		try{
			queue.remove();
		}catch(AssertionError exception){}
		
		for(int i=0;i<10;i++){
			queue.add(i);
		}
		
		for(int i=0;i<10;i++){
			assertFalse("test empty (FALSE)",queue.isEmpty());
			assertEquals("test size",queue.size(),10-i);

			assertEquals("test top",queue.top(),i);
			queue.remove();
		}
		
		assertTrue("test empty (TRUE)",queue.isEmpty());	
	}

}
