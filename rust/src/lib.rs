//! Tiny library exercising rules_rust + crate_universe deps (anyhow, serde, serde_json).

use serde::{Deserialize, Serialize};

#[derive(Debug, PartialEq, Serialize, Deserialize)]
pub struct Greeting {
    pub name: String,
    pub message: String,
}

impl Greeting {
    pub fn new(name: &str) -> Self {
        Greeting {
            name: name.to_string(),
            message: format!("Hello, {}!", name),
        }
    }

    /// Serialize to JSON.
    pub fn to_json(&self) -> anyhow::Result<String> {
        Ok(serde_json::to_string(self)?)
    }

    /// Parse from JSON, rejecting an empty name.
    pub fn from_json(json: &str) -> anyhow::Result<Self> {
        let g: Greeting = serde_json::from_str(json)?;
        anyhow::ensure!(!g.name.is_empty(), "name must not be empty");
        Ok(g)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn json_round_trip() {
        let g = Greeting::new("Bazel");
        let json = g.to_json().unwrap();
        assert_eq!(json, r#"{"name":"Bazel","message":"Hello, Bazel!"}"#);
        assert_eq!(Greeting::from_json(&json).unwrap(), g);
    }

    #[test]
    fn empty_name_is_an_error() {
        let err = Greeting::from_json(r#"{"name":"","message":""}"#).unwrap_err();
        assert!(err.to_string().contains("name must not be empty"));
    }
}
