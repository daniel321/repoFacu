package daniel;

import static org.junit.Assert.*;

// Queue class
public class AQueue implements Queue {
	private Node beginning = null;
	private Node end = null;
	
	// returns weather if the queue is empty or not
	public boolean isEmpty() {
		return (size() == 0);
	}

	// returns the size of the queue
	public int size() {
		return (beginning == null)? 0:beginning.countConnectedNodes(0);
	}

	// adds a new item at the end of the queue
	public void add(Object newData) {
		end = (end == null) ? new Node(newData) : end.addAndReturn(newData);
		beginning = (beginning == null)? end : beginning;	
	}

	// returns the element at the beginning of the queue
	public Object top() throws AssertionError {
		if(beginning==null) throw new AssertionError();
		return beginning.getData();
	}

	// removes the element at the beginning of the queue
	public void remove() throws AssertionError{
		if(beginning==null) throw new AssertionError();
		beginning = beginning.next();
	}

	// Node class
	private class Node{
		private Node next = null;
		private Object data = null;	
		
		// constructor
		public Node(Object NewData) {
			data = NewData;
		}

		// returns the node next to "this" one
		public Node next() {
			return next;
		}
		
		// adds a new node next to "this" one and returns it
		public Node addAndReturn(Object NewData){
			return (next = new Node(NewData));
		}

		// returns the data
		public Object getData(){
			return data;
		}
		
		// counts all nodes from this one forward and returns the result
		public int countConnectedNodes(int counter){
			return ((next == null)? counter+1 : next.countConnectedNodes(counter+1));
		}
	}
}
