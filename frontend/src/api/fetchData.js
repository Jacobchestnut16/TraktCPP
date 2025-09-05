// frontend/src/api/fetchData.js
export async function getAnalytics() {
    const res = await fetch("http://localhost:8080/api/analytics");
    return res.json();
}
