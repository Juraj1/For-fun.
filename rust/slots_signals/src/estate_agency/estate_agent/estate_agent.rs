use std::collections::HashMap;
use std::sync::{Arc, Mutex};

pub struct EstateAgent {
}

pub trait EstateAgentTrait {
    fn new() -> Self;
    fn change_estate_ownership(&self, estates: Arc<Mutex<HashMap<String, (String, f64)>>>, estate_name: &str, new_owner_name: &str);
}

impl EstateAgentTrait for EstateAgent {
    fn new() -> EstateAgent {
        EstateAgent {}
    }
    fn change_estate_ownership(&self, estates: Arc<Mutex<HashMap<String, (String, f64)>>>, estate_name: &str, new_owner_name: &str) {
        let mut var = match estates.lock().unwrap().remove(estate_name) {
            Some(var) => var,
            None => panic!("EstateAgent failed to change estate ownership!"),
        };
        var.0 = new_owner_name.to_string();
        estates.lock().unwrap().insert(estate_name.to_string(), var);
    }
}

