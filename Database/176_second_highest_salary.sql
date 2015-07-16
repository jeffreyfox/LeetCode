# distinct is needed
# IFNULL is needed to return null when no second highest salary exist

SELECT IFNULL( (SELECT distinct Salary FROM Employee ORDER BY Salary DESC LIMIT 1, 1) , null);
