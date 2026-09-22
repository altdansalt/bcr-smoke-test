use bcr_smoke_rust::Greeting;

fn main() -> anyhow::Result<()> {
    let name = std::env::args().nth(1).unwrap_or_else(|| "world".to_string());
    println!("{}", Greeting::new(&name).to_json()?);
    Ok(())
}
