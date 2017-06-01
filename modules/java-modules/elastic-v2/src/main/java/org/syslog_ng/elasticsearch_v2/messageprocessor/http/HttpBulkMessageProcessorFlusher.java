package org.syslog_ng.elasticsearch_v2.messageprocessor.http;

public class HttpBulkMessageProcessorFlusher extends Thread {
	private boolean run;
	private HttpMessageProcessor processor;
	private long flushTimeout;
	
	public HttpBulkMessageProcessorFlusher (HttpMessageProcessor processor, long flushTimeout) {
		this.run = true;
		this.processor = processor;
		this.flushTimeout = flushTimeout;
	}
	
	@Override
	public void run () {
		
		if(this.flushTimeout < 1)
			return;
		
		while(this.run) {
			try {
				Thread.sleep(flushTimeout);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			try {
				this.processor.flush();
			} catch (Exception e) {
				// can be not initialized if flush interval is too low
			}
		}
		
	}
	
	public void stopRun() {
		this.run = false;
	}
}
