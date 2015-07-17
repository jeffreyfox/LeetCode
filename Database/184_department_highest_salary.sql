SELECT Department.Name AS Department, e1.Name AS Employee, e1.Salary AS Salary
FROM Employee e1 JOIN Department ON e1.DepartmentId=Department.Id
WHERE e1.Salary = (SELECT MAX(e2.Salary) FROM Employee e2 WHERE e1.DepartmentId=e2.DepartmentId);
