use std::collections::HashMap;
use std::sync::{Arc, Mutex};
use signals2::*;
use crate::estate_agency::estate_agent::estate_agent::{EstateAgent, EstateAgentTrait};

pub struct SignalHandler{
    // Signals
    /// (EstateAgent ref), (estate_name: String), (new_owner: String), (estates: &mut HashMap(name, (owner, value));
    pub sig_change_estate_owner: Signal<(
        Arc<Mutex<EstateAgent>>,
        String,
        String,
        Arc<Mutex<HashMap<String, (String, f64)>>>
        ,), bool>
}

impl SignalHandler{
    pub fn new() -> SignalHandler{
        SignalHandler {
            sig_change_estate_owner: Signal::new()
        }
    }
    pub fn connect_handlers(&self) {
        self.sig_change_estate_owner.connect(slot_sell_estate);
    }
}
fn slot_sell_estate(estate_agent: Arc<Mutex<EstateAgent>>,
                    estate_name: String,
                    new_owner: String,
                    estates: Arc<Mutex<HashMap<String, (String, f64)>>>) -> bool {
    estate_agent.lock().unwrap().change_estate_ownership(estates.clone(), &estate_name, &new_owner);
    println!("Changed estate ownership to: {}", new_owner);
    true
}