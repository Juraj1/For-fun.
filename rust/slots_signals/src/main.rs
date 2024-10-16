mod bank;
mod estate_agency;
mod customer;
mod memory;
mod signal_handler;

use std::sync::{Arc, Mutex};
use signals2::*;
use crate::memory::Memory;
use crate::signal_handler::SignalHandler;
use crate::signal_handler::*;



fn main() {
    // customer
    let martin = "Martin".to_string();
    // agent
    let robert = "Robert".to_string();

    let mut memory = Memory::new(&robert, &martin);
    memory.memory_init();

    let signal_handler = SignalHandler::new();
    signal_handler.connect_handlers();
    let ret = signal_handler.sig_change_estate_owner.emit(memory.estate_agent.clone(), "estate1".to_string(), martin, memory.estates.clone());
    println!("Ending program");
}


