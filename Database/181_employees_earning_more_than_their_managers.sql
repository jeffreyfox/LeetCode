SELECT Employee.Name AS Employee 
FROM 
Employee INNER JOIN Employee AS Manager
ON Employee.ManagerId=Manager.Id
WHERE Employee.Salary > Manager.Salary
